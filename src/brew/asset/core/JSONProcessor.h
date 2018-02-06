/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 28.09.16
 *
 */

#ifndef BREW_JSONPROCESSOR_H
#define BREW_JSONPROCESSOR_H

#include <brew/asset/AssetProcessor.h>
#include <brew/video/VideoContext.h>

#include "json/json.hpp"

namespace brew {

using json = nlohmann::json;

/**
 * The JSON processing parameters.
 */
class JSONProcessorParams : public AssetProcessorParams {};

/**
 * An asset processor for JSON data.
 */
class JSONProcessor : public AssetProcessor<JSONProcessorParams> {
public:
    /**
     * Loads a given asset.
     * @param assetPipeline The pipeline the asset is loaded in.
     * @param vfs The file system to read from.
     * @param bundle The bundle to store the results in.
     * @param tag The tag or filename of the asset to load.
     * @param params The processing parameters.
     */
    void load(AssetPipeline& assetPipeline,
              const VirtualFileSystem& vfs,
              AssetBundle& bundle,
              const String& tag,
              const JSONProcessorParams& params) const override;

    /**
     * Checks whether this processor can load the given asset.
     * @param assetPipeline The pipeline the asset is loaded in.
     * @param vfs The file system to read from.
     * @param bundle The bundle to store the results in.
     * @param tag The tag or filename of the asset to load.
     * @param params The processing parameters.
     */
    bool canLoad(const AssetPipeline& assetPipeline,
                 const VirtualFileSystem& vfs,
                 const AssetBundle& bundle,
                 const String& tag,
                 const JSONProcessorParams& params) const override;

    /**
     * Checks whether a type hint is accepted by this processor.
     * @param typeHint The type hint.
     * @return Whether the given type hint is accepted.
     */
    bool acceptsType(const String& typeHint) const override;
};

} /* namespace brew */

#endif //BREW_JSONPROCESSOR_H
