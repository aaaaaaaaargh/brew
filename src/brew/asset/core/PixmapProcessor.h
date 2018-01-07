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

#ifndef BREW_PIXMAPPROCESSOR_H
#define BREW_PIXMAPPROCESSOR_H

#include <brew/asset/AssetProcessor.h>

namespace brew {

class PixmapProcessorParams : public AssetProcessorParams {

};

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
                      const PixmapProcessorParams& params) override;

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
                         const PixmapProcessorParams& params) override;
};

} /* namespace brew */

#endif //BREW_PIXMAPPROCESSOR_H
