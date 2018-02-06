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

#ifndef BREW_TEXTUREPROCESSOR_H
#define BREW_TEXTUREPROCESSOR_H

#include <brew/asset/AssetProcessor.h>
#include <brew/video/VideoContext.h>

namespace brew {

/**
 * The texture processing parameters.
 */
class TextureProcessorParams : public AssetProcessorParams {
public:
    explicit TextureProcessorParams(VideoContext& context);

public:
    VideoContext& context; //< The video context to use.
    bool freeSourcePixmap = true; //< Whether to release the source pixmap asset after texture creation.
    TextureFiltering filtering = TextureFiltering::Bilinear; //< The texture filtering.
};

/**
 * An asset processor for textures.
 */
class TextureProcessor : public AssetProcessor<TextureProcessorParams> {
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
              const TextureProcessorParams& params) const override;

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
                 const TextureProcessorParams& params) const override;

    /**
     * Checks whether a type hint is accepted by this processor.
     * @param typeHint The type hint.
     * @return Whether the given type hint is accepted.
     */
    bool acceptsType(const String& typeHint) const override;
};

} /* namespace brew */

#endif //BREW_TEXTUREPROCESSOR_H
