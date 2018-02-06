/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Dec 31, 2016
 *
 */

#include <brew/asset/core/TextureAtlasProcessor.h>
#include <brew/asset/core/JSONProcessor.h>
#include <brew/asset/AssetPipeline.h>
#include <brew/video/TextureAtlas.h>

namespace brew {

void brew::TextureAtlasProcessor::load(AssetPipeline& assetPipeline, const VirtualFileSystem& vfs, AssetBundle& bundle,
                               const String& tag, const TextureAtlasProcessorParams& params) const {
    if(!assetPipeline.load(tag, "json").getResult()) {
        throw RuntimeException("Could not load atlas data.");
    }

    auto jsonAtlasPtr = bundle.get<json>(tag);
    auto jsonAtlas = *jsonAtlasPtr;

    // Get the textures.
    auto jsonTextures = jsonAtlas["textures"];

    auto atlas = std::make_shared<TextureAtlas>();

    bundle.put(tag, atlas);

    String prefix = tag.substr(0, tag.find_last_of('/'))+"/";

    // Iterate over the textures and extract the regions.
    for(json::iterator it = jsonTextures.begin(); it != jsonTextures.end(); ++it) {
        String fileName = it.key();
        // Load the texture.
        auto textureName = prefix + fileName;

        if(!assetPipeline.load(textureName, "texture").getResult()) {
            throw RuntimeException("Could not load atlas texture '" + textureName + "'.");
        }

        auto tex = bundle.get<Texture>(textureName);

        auto jsonRegions = it.value()["regions"];
        for(json::iterator it = jsonRegions.begin(); it != jsonRegions.end(); ++it) {
            String regionName = it.key();
            auto jsonRegion = it.value()["region"];

            int x = jsonRegion[0];
            int y = jsonRegion[1];
            int w = jsonRegion[2];
            int h = jsonRegion[3];

            atlas->addRegion(regionName, TextureRegion(tex, RealRect(x,y,w,h)));
        }
    }
}

bool TextureAtlasProcessor::canLoad(const AssetPipeline& assetPipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle,
                            const String& tag, const TextureAtlasProcessorParams& params) const {
    return true;
}

bool TextureAtlasProcessor::acceptsType(const String& typeHint) const {
    return typeHint == "textureAtlas";
}

} /* namespace brew */