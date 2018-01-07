/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 07.09.17
 *
 */

#include <brew/video/FrameBuffer.h>
#include <brew/video/VideoContext.h>

namespace brew {

FrameBuffer::FrameBuffer(VideoContext& context,
                         SizeT width, SizeT height,
                         u8 numColorAttachments,
                         bool hasDepthAttachment,
                         bool hasStencilAttachment)
        : width(width),
          height(height),
          _hasDepthAttachment(hasDepthAttachment),
          _hasStencilAttachment(hasStencilAttachment)
{
    for(u8 i=0; i < numColorAttachments; ++i) {
        auto tex = context.createTexture(width, height, Color::BLACK, TextureFormat::RGB8U, TextureFiltering::None, 0);
        colorTextures.push_back(tex);
    }

    if(hasDepthAttachment) {
        auto depthTex = context.createTexture(width, height, Color::BLACK, TextureFormat::Depth, TextureFiltering::None, 0);
        depthTexture = std::move(depthTex);
    }

}
} /* namespace brew */
