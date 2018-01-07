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

class AssetManager : public detail::AbstractAssetManager, public Object {
public:
    using AbstractAssetManager::AbstractAssetManager;

    template<typename... ProcessorParamsT>
    AssetPromise load(const String& tag, ProcessorParamsT &&... params) {
        // Create a new pipeline and process the asset.
        return AssetPipeline::request(*this, tag, nullptr, params...);
    };

    template<typename AssetProcessorT, typename ProcessorParamsT=typename AssetProcessorT::params_type>
    void registerProcessor(const ProcessorParamsT defaultProcessorParams = ProcessorParamsT()) {
        auto hash = typeid(AssetProcessorT).hash_code();
        auto& entry = processors[hash];

        entry.processor = std::make_unique<AssetProcessorT>();
        entry.processor->setAppContextFrom(*this);

        entry.paramsTypeHash = typeid(AssetProcessorT).hash_code();
        entry.params = std::make_unique<ProcessorParamsT>(defaultProcessorParams);
    };
};



} /* namespace brew */

#endif //BREW_ASSETMANAGER_H
