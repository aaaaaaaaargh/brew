/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 02.01.18
 *
 */

#ifndef BREW_ASSETMANAGER_H
#define BREW_ASSETMANAGER_H

#include <brew/asset/AssetBundle.h>
#include <brew/fileio/VirtualFileSystem.h>

#include <functional>
#include <iostream>
#include <thread>
#include <future>

namespace brew {

class AssetManager;
class AssetProcessorParams;
class AssetPipeline;

class AbstractAssetProcessor {
    friend class AssetPipeline;

protected:
    virtual void invoke(AssetPipeline& pipeline, const String& tag, const AssetProcessorParams& params) = 0;
    virtual bool check(const AssetPipeline& pipeline, const String& tag, const AssetProcessorParams& params) = 0;
};

class AssetProcessorParams {};

class AbstractAssetManager {
protected:
    friend class AssetPipeline;
    friend class AssetManager;

private:
    struct ParamsInfo {
        SizeT typeHash;
        std::shared_ptr<AssetProcessorParams> params;
    };

    struct ProcessorInvocationOptions {
        std::shared_ptr<ParamsInfo>& thisParamsInfo;
        std::vector<std::unique_ptr<ParamsInfo> >& paramsInfo;
    };

    struct ProcessorEntry {
        std::unique_ptr<AbstractAssetProcessor> processor;
        SizeT paramsTypeHash;
        std::shared_ptr<AssetProcessorParams> params;
        std::function<void(const ProcessorInvocationOptions&)> invoke;
    };

    std::shared_ptr<VirtualFileSystem> vfs;
    std::map<SizeT, ProcessorEntry> processors;
};

class AssetPromise {
private:
    friend class AssetPipeline;

    AssetPromise(
            std::shared_ptr<AssetPipeline> && pipeline,
            std::shared_ptr<std::promise<bool> > && promise
    ) : pipeline(pipeline), promise(promise) {}

public:
    bool getResult();

private:
    std::shared_ptr<std::promise<bool> > promise;
    std::shared_ptr<AssetPipeline> pipeline;
};

class AssetPipeline {
public:
    explicit AssetPipeline(AbstractAssetManager& assetManager)
    : manager(assetManager), parent(nullptr) {
    }

    ~AssetPipeline() {
        // Make sure we block until all sub-threads are ready.
        for(auto& thd : runningThreads) {
            thd.join();
        }
    }

public:
    AssetManager& getManager();

private:
    typedef AbstractAssetManager::ParamsInfo ParamsInfo;

private:
    template<typename... ProcessorParamsT>
    static AssetPromise request(AbstractAssetManager& assetManager, const String& tag, AssetPipeline* parent, ProcessorParamsT &&... params) {
        auto promise = std::make_shared<std::promise<bool> >();

        auto pipeline = std::make_shared<AssetPipeline>(assetManager);
        pipeline->parent = parent;

        makeParams(pipeline->paramsInfo, params...);

        pipeline->invoke(tag, promise);

        return AssetPromise(std::move(pipeline), std::move(promise));
    };

public:
    template<typename... ProcessorParamsT>
    AssetPromise load(const String& tag, ProcessorParamsT &&... params) {
        return request(manager, tag, this, params...);
    };

private:
    template<typename... ProcessorParamsT>
    void invoke(const String& tag, std::shared_ptr<std::promise<bool> > promise, ProcessorParamsT &&... params) {
        std::vector<std::shared_ptr<ParamsInfo> > thisParamsInfo;
        makeParams(thisParamsInfo, params...);

        // Append the local parameters.
        for(auto& localParam : paramsInfo) {
            thisParamsInfo.push_back(localParam);
        }

        // Find the a matching processor.
        for(auto& procInfo : manager.processors) {
            auto &proc = *procInfo.second.processor;

            // Find params.
            AssetProcessorParams* procParams = nullptr;

            for(auto& paramInfo : thisParamsInfo) {
                if(paramInfo->typeHash == procInfo.second.paramsTypeHash) {
                    // Found
                    procParams = paramInfo->params.get();
                    break;
                }
            }

            if(!procParams) {
                // Get default params.
                procParams = procInfo.second.params.get();
            }

            if(proc.check(*this, tag, *procParams)) {
                // Start a new thread and add it to running threads.
                runningThreads.push_back(std::thread([=, &proc] {
                    proc.invoke(*this, tag, *procParams);
                    promise->set_value(true);
                }));

                // Done.
                return;
            }
        }

        // No processor found.
        promise->set_value(false);
    }

private:
    friend class AssetManager;

    template<typename P0, typename... ProcessorParamsT>
    static void makeParams(std::vector<std::shared_ptr<ParamsInfo> >& paramsInfo, P0 && p0, ProcessorParamsT... params) {
        auto info = std::make_shared<ParamsInfo>();
        info->typeHash = typeid(P0).hash_code();

        paramsInfo.emplace_back(std::move(info));

        makeParams(paramsInfo, params...);
    }

    static void makeParams(std::vector<std::shared_ptr<ParamsInfo> >& paramsInfo);

private:
    AbstractAssetManager& manager;
    std::vector<std::shared_ptr<ParamsInfo> > paramsInfo;
    AssetPipeline* parent;

    std::vector<std::thread> runningThreads;
};

class AssetManager : public AbstractAssetManager {
public:
    explicit AssetManager(std::shared_ptr<VirtualFileSystem> vfs);

    template<typename... ProcessorParamsT>
    AssetPromise load(const String& tag, ProcessorParamsT &&... params) {
        // Create a new pipeline and process the asset.
        return AssetPipeline::request(*this, tag, nullptr, params...);
    };

    template<typename AssetProcessorT, typename ProcessorParamsT>
    void registerProcessor(const ProcessorParamsT defaultProcessorParams = ProcessorParamsT()) {
        auto hash = typeid(AssetProcessorT).hash_code();
        auto& entry = processors[hash];

        entry.processor = std::make_unique<AssetProcessorT>();
        entry.paramsTypeHash = typeid(AssetProcessorT).hash_code();
        entry.params = std::make_unique<ProcessorParamsT>(defaultProcessorParams);
    };
};

template<typename ParamsT>
class AssetProcessor : public AbstractAssetProcessor {
protected:
    inline void invoke(AssetPipeline& pipeline, const String& tag, const AssetProcessorParams& params) final {
        load(pipeline, tag, static_cast<const ParamsT&>(params));
    }

    inline bool check(const AssetPipeline& pipeline, const String& tag, const AssetProcessorParams& params) final {
        return canLoad(pipeline, tag, static_cast<const ParamsT&>(params));
    }

public:
    virtual void load(AssetPipeline& assetPipeline, const String& tag, const ParamsT& params) = 0;
    virtual bool canLoad(const AssetPipeline& assetPipeline, const String& tag, const ParamsT& params) = 0;
};

}

#endif //BREW_ASSETMANAGER_H
