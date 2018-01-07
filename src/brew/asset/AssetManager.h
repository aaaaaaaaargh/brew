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

#include <brew/fileio/VirtualFileSystem.h>

namespace brew {

class AssetBundle {
private:
    struct AbstractWrappedAsset {};

    template<typename AssetT>
    struct WrappedAsset : AbstractWrappedAsset {
        std::unique_ptr<AssetT> asset;
    };

public:
    typedef std::map<String, std::unique_ptr<AbstractWrappedAsset> > AssetMap;

public:
    template <typename AssetT>
    void put(const String& name, AssetT asset) {
        put(name, std::make_unique<AssetT>(asset));
    }

    template <typename AssetT>
    void put(const String& name, std::unique_ptr<AssetT> && asset) {
        auto hash = typeid(AssetT).hash_code();

        auto wrappedAsset = std::make_unique<WrappedAsset<AssetT> >();
        wrappedAsset->asset = std::move(asset);

        assets[hash][name] = std::unique_ptr<AbstractWrappedAsset>(wrappedAsset.release());
    }

    template <typename AssetT>
    AssetT& get(const String& name) const {
        auto hash = typeid(AssetT).hash_code();
        auto mapIt = assets.find(hash);

        if(mapIt != assets.end()) {
            auto it = mapIt->second.find(name);
            if(it != mapIt->second.end()) {
                auto& wrappedAsset = static_cast<WrappedAsset<AssetT>&>(*it->second);
                return *wrappedAsset.asset;
            }
        }

        throw NotFoundException("No such asset '" + name + "' for given type.");
    }

    template <typename AssetT>
    AssetT& remove(const String& name) {
        auto hash = typeid(AssetT).hash_code();
        auto mapIt = assets.find(hash);

        if(mapIt != assets.end()) {
            mapIt->second.erase(name);
        }
    }

    void removeAll(const String& name) {
        for(auto& e : assets) {
            e.second.erase(name);
        }
    }

private:
    std::map<
            SizeT, // Asset type hash
            AssetMap
            > assets;
};

class AbstractAssetProcessor {

};

class AssetProcessorParams {};

class AssetManager : public AssetBundle {
public:
    AssetManager(std::shared_ptr<VirtualFileSystem> vfs);

    template<typename AssetT, typename... ProcessorParamsT>
    void load(const String& tag, ProcessorParamsT && ... params, std::function<void(AssetT&)> callback) {

    };

    template<typename AssetProcessorT, typename ProcessorParamsT>
    void registerProcessor(const ProcessorParamsT defaultProcessorParams = ProcessorParamsT()) {
        auto hash = typeid(AssetProcessorT).hash_code();
        auto& entry = processors[hash];

        entry.processor = std::make_unique<AssetProcessorT>();
        entry.paramsTypeHash = typeid(AssetProcessorT).hash_code();
    };

private:
    struct ProcessorEntry {
        std::unique_ptr<AbstractAssetProcessor> processor;
        SizeT paramsTypeHash;
    };

    std::shared_ptr<VirtualFileSystem> vfs;
    std::map<SizeT, ProcessorEntry> processors;
};

////////////////////////////

template<typename ConsumedT>
class AssetProcessor {
public:
    typedef ConsumedT consumed_type;
};

class AssetPipeline {
public:
    template<typename ProcessorT>
    void registerProcessor() {

    }

    template<typename ConsumedT>
    void processAsset();
};



}

#endif //BREW_ASSETMANAGER_H
