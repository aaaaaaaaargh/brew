/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 23.09.16
 *
 */

#ifndef BREW_PIXMAPPROCESSOR_H
#define BREW_PIXMAPPROCESSOR_H

#include <brew/asset/AssetProcessor.h>

namespace brew {

/**
 * The pixmap processing parameters.
 */
class PixmapProcessorParams : public AssetProcessorParams {
public:
    bool invertYAxis = false; //< Whether to invert the y axis of the pixmap. Useful for texture generation.
};

/**
 * An asset processor for pixmaps.
 */
class PixmapProcessor : public AssetProcessor<PixmapProcessorParams> {
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
                      const PixmapProcessorParams& params) const override;

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
                         const PixmapProcessorParams& params) const override;

    /**
     * Checks whether a type hint is accepted by this processor.
     * @param typeHint The type hint.
     * @return Whether the given type hint is accepted.
     */
    bool acceptsType(const String& typeHint) const override;
};

} /* namespace brew */

#endif //BREW_PIXMAPPROCESSOR_H
