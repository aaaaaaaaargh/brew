/**
 *  Copyright 2015-2018 random arts
 *  Created on: 07.01.18
 */

#include <brew/asset/core/CoreAssetProcessors.h>

#include <brew/asset/core/PixmapProcessor.h>

void brew::CoreAssetProcessors::registerTo(brew::AssetManager& assetManager) {
    assetManager.registerProcessor<PixmapProcessor>();
}
