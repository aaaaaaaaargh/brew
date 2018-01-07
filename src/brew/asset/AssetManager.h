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

#ifndef BREW_ASSETMANAGER_H
#define BREW_ASSETMANAGER_H

#include <brew/asset/AbstractAssetManager.h>

#include <brew/asset/AssetPromise.h>
#include <brew/asset/AssetPipeline.h>
#include <brew/core/Object.h>

namespace brew {

/**
 * The asset manager provides an extendible framework for loading and processing of assets loaded from file system.
 */
class AssetManager : public detail::AbstractAssetManager, public Object {
public:
    using AbstractAssetManager::AbstractAssetManager;

    /**
     * Loads a new asset.
     * @tparam ProcessorParamsT The processing parameter types for the asset processors.
     * @param tag The asset tag or filename.
     * @param typeHint A type hint or an empty string to ignore type hinting.
     * @param params The processing parameters for the asset processors.
     * @return A promise resolved when the asset has been loaded or an error occurred.
     */
    template<typename... ProcessorParamsT>
    AssetPromise load(const String& tag, const String& typeHint, ProcessorParamsT &&... params) {
        // Create a new pipeline and process the asset.
        return AssetPipeline::request(*this, tag, typeHint, nullptr, params...);
    };

    /**
     * Registers a new asset processor.
     * @tparam AssetProcessorT The asset processor type to register.
     * @param defaultProcessorParams The default asset processor parameters.
     */
    template<typename AssetProcessorT>
    void registerProcessor(const typename AssetProcessorT::params_type defaultProcessorParams = typename AssetProcessorT::params_type()) {
        typedef typename AssetProcessorT::params_type ProcessorParamsT;

        auto hash = typeid(AssetProcessorT).hash_code();
        auto& entry = processors[hash];

        entry.processor = std::make_unique<AssetProcessorT>();
        entry.processor->setAppContextFrom(*this);

        entry.paramsTypeHash = typeid(ProcessorParamsT).hash_code();

        entry.params = std::make_unique<ProcessorParamsT>(defaultProcessorParams);
    };
};



} /* namespace brew */

#endif //BREW_ASSETMANAGER_H
