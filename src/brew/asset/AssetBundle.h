/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 07.01.18
 *
 */

#ifndef BREW_ASSETBUNDLE_H
#define BREW_ASSETBUNDLE_H

#include <brew/core/Types.h>
#include <brew/core/Exception.h>

#include <memory>
#include <map>

namespace brew {

/**
 * A class that contains assets of any given type.
 * Once an asset is put into a bundle, the bundle takes ownership on the object, meaning that deleting a bundle
 * will cause all contained assets to be unloaded as well.
 */
class AssetBundle {
private:
    struct AbstractWrappedAsset {};

    template<typename AssetT>
    struct WrappedAsset : AbstractWrappedAsset {
        std::shared_ptr<AssetT> asset;
    };

public:
    typedef std::map<String, std::unique_ptr<AbstractWrappedAsset> > AssetMap; //< A map of assets.

public:
    /**
     * Adds a new asset to the bundle.
     * @tparam AssetT The asset type.
     * @param name The asset name.
     * @param asset A pointer containing the asset to add.
     */
    template <typename AssetT>
    void put(const String& name, std::shared_ptr<AssetT> asset) {
        auto hash = typeid(AssetT).hash_code();

        auto wrappedAsset = std::make_unique<WrappedAsset<AssetT> >();
        wrappedAsset->asset = std::move(asset);

        assets[hash][name] = std::unique_ptr<AbstractWrappedAsset>(wrappedAsset.release());
    }

    /**
     * Adds a new asset to the bundle.
     * @tparam AssetT The asset type.
     * @param name The asset name.
     * @param asset The asset to add.
     */
    template <typename AssetT>
    void put(const String& name, AssetT& asset) {
        put(name, std::shared_ptr<AssetT>(asset));
    }

    /**
     * Gets an asset from the bundle.
     * @tparam AssetT The asset type.
     * @param name The asset name.
     * @return The asset.
     * @throws NotFoundException if there is no asset with the given type and name.
     */
    template <typename AssetT>
    std::shared_ptr<AssetT> get(const String& name) const {
        auto hash = typeid(AssetT).hash_code();
        auto mapIt = assets.find(hash);

        if(mapIt != assets.end()) {
            auto it = mapIt->second.find(name);
            if(it != mapIt->second.end()) {
                auto& wrappedAsset = static_cast<WrappedAsset<AssetT>&>(*it->second);
                return wrappedAsset.asset;
            }
        }

        throw NotFoundException("No such asset '" + name + "' for given type.");
    }
    /**
     * Checks if an asset exists.
     * @tparam AssetT The asset type.
     * @param name The asset name.
     * @return Whether the asset exists.
     */
    template <typename AssetT>
    bool contains(const String& name) const {
        auto hash = typeid(AssetT).hash_code();
        auto mapIt = assets.find(hash);

        if(mapIt != assets.end()) {
            auto it = mapIt->second.find(name);
            if (it != mapIt->second.end()) {
                return true;
            }
        }

        return false;
    }

    /**
     * Removes an asset from the bundle.
     * @tparam AssetT The asset type.
     * @param name The asset name.
     * @return
     */
    template <typename AssetT>
    void remove(const String& name) {
        auto hash = typeid(AssetT).hash_code();
        auto mapIt = assets.find(hash);

        if(mapIt != assets.end()) {
            mapIt->second.erase(name);
        }
    }

    /**
     * Removes all assets with a given name.
     * @param name The asset name.
     */
    void removeAll(const String& name) {
        for(auto& e : assets) {
            e.second.erase(name);
        }
    }

    /**
     * Removes all assets of a given type.
     * @tparam AssetT The asset type.
     */
    template<typename AssetT>
    void removeAll() {
        auto hash = typeid(AssetT).hash_code();
        assets.erase(hash);
    }

private:
    std::map<
    SizeT, // Asset type hash
    AssetMap
    > assets;
};

} /* namespace brew */

#endif //BREW_ASSETBUNDLE_H
