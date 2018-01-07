/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 02.01.18
 *
 */

#ifndef BREW_ASSETPIPELINE_H
#define BREW_ASSETPIPELINE_H

#include <brew/core/Types.h>

#include <brew/asset/AbstractAssetManager.h>
#include <brew/asset/AssetPromise.h>

#include <thread>
#include <future>
#include <vector>

namespace brew {

class AssetProcessorParams;

/**
 * An asset that is being loaded via the asset manager can be processed by multiple asset processors.
 * The asset pipeline is handling asynchronous and global states as long as at least one processor is still loading
 * dependencies or processing the loaded asset.
 *
 * Pipelines are not created manually, each call to AssetManager::load() or AssetPipeline::load() will create a
 * new instance that is using the current processing context.
 */
class AssetPipeline {
public:
    /**
     * Creates a new asset pipeline.
     * @param assetManager The asset manager that spawned this instance.
     */
    explicit AssetPipeline(detail::AbstractAssetManager& assetManager)
            : manager(assetManager), parent(nullptr) {
    }

    /**
     * Destroys the pipeline, waiting for any pending requests.
     */
    ~AssetPipeline() {
        // Make sure we block until all sub-threads are ready.
        for(auto& thd : runningThreads) {
            thd.join();
        }
    }

private:
    typedef detail::AbstractAssetManager::ParamsInfo ParamsInfo;

private:
    template<typename... ProcessorParamsT>
    static AssetPromise request(detail::AbstractAssetManager& assetManager, const String& tag, const String& typeHint, AssetPipeline* parent, ProcessorParamsT &&... params) {
        auto promise = std::make_shared<std::promise<bool> >();

        auto pipeline = std::make_shared<AssetPipeline>(assetManager);
        pipeline->parent = parent;

        makeParams(pipeline->paramsInfo, params...);

        pipeline->invoke(tag, typeHint, promise, params...);

        return AssetPromise(std::move(pipeline), std::move(promise));
    };

public:
    /**
     * Loads an asset.
     * @tparam ProcessorParamsT The optional processing parameters, will be mapped to a processor by its type.
     * @param tag The asset tag or filename.
     * @param params The loading parameters.
     * @return A promise resolved once the asset has been loaded or an error occured.
     */
    template<typename... ProcessorParamsT>
    AssetPromise load(const String& tag, const String& typeHint, ProcessorParamsT &&... params) {
        return request(manager, tag, typeHint, this, params...);
    };

private:
    template<typename... ProcessorParamsT>
    void invoke(const String& tag, const String& typeHint, std::shared_ptr<std::promise<bool> > promise, ProcessorParamsT &&... params) {
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

            // Get the bundle.
            auto bundle = &manager.getDefaultBundle();

            if(typeHint == "" || proc.acceptsType(typeHint)) {
                // Type is accepted.
                if (proc.check(*this, *manager.vfs, *bundle, tag, *procParams)) {
                    // Start a new thread and add it to running threads.
                    runningThreads.push_back(std::thread([=, &proc] {
                        proc.invoke(*this, *manager.vfs, *bundle, tag, *procParams);
                        promise->set_value(true);
                    }));

                    // Done.
                    return;
                }
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
    detail::AbstractAssetManager& manager;
    std::vector<std::shared_ptr<ParamsInfo> > paramsInfo;
    AssetPipeline* parent;
    std::vector<std::thread> runningThreads;
};

} /* namespace brew */

#endif //BREW_ASSETPIPELINE_H
