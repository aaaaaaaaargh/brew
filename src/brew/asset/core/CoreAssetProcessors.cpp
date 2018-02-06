/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 07.01.18
 *
 */

#include <brew/asset/core/CoreAssetProcessors.h>

#include <brew/asset/core/PixmapProcessor.h>
#include <brew/asset/core/TextureProcessor.h>
#include <brew/asset/core/BitmapFontProcessor.h>
#include <brew/asset/core/JSONProcessor.h>
#include <brew/asset/core/TextureAtlasProcessor.h>

void brew::CoreAssetProcessors::registerTo(brew::AssetManager& assetManager, VideoContext& videoContext) {
    {
        assetManager.registerProcessor<PixmapProcessor>();
    }

    {
        TextureProcessorParams params(videoContext);
        assetManager.registerProcessor<TextureProcessor>(params);
    }

    {
        assetManager.registerProcessor<BitmapFontProcessor>();
    }

    {
        assetManager.registerProcessor<JSONProcessor>();
    }

    {
        assetManager.registerProcessor<TextureAtlasProcessor>();
    }

}
