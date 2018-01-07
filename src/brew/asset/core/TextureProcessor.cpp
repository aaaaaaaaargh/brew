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

#include <brew/asset/core/TextureProcessor.h>
#include <brew/asset/AssetPipeline.h>
#include <brew/video/Texture.h>

namespace brew {

TextureProcessorParams::TextureProcessorParams(VideoContext& context)
: context(context) {
}

void TextureProcessor::load(AssetPipeline& assetPipeline, const VirtualFileSystem& vfs, AssetBundle& bundle,
                            const String& tag, const TextureProcessorParams& params) const {
    if(!assetPipeline.load(tag, "pixmap").getResult()) {
        throw RuntimeException("Could not load image.");
    }

    getAppContext().log->stream("TextureProcessor") << LogLevel::Debug << "Loading '" << tag << "' ...";

    auto pixmap = bundle.get<Pixmap>(tag);

    auto texture = params.context.createTexture(*pixmap);
    bundle.put(tag, texture);
}

bool TextureProcessor::canLoad(const AssetPipeline& assetPipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle,
                          const String& tag, const TextureProcessorParams& params) const {
    return true;
}

bool TextureProcessor::acceptsType(const String& typeHint) const {
    return typeHint == "texture";
}

} /* namespace brew */