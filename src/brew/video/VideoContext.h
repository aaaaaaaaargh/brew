/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 04.09.17
 *
 */

#ifndef BREW_VIDEOCONTEXT_H
#define BREW_VIDEOCONTEXT_H

#include <brew/core/ProxyObjectManager.h>
#include <brew/core/Object.h>
#include <brew/video/Color.h>

#include <brew/video/Texture.h>
#include <brew/video/FrameBuffer.h>
#include <brew/video/ShaderVariables.h>
#include <brew/video/VertexBuffer.h>

namespace brew {

class VideoContext :
        public Object,
        private ProxyObjectManager<Texture, TextureContextHandle>,
        private ProxyObjectManager<FrameBuffer, FrameBufferContextHandle>,
        private ProxyObjectManager<ShaderVariables, ShaderVariablesContextHandle>,
        private ProxyObjectManager<VertexBuffer, VertexBufferContextHandle>
{
public:
    /**
     * Initializes pending context objects. Should not be called manually.
     */
    void processPendingOperations();

public:
    /**
     * Creates a new empty texture.
     * @param width The texture width.
     * @param height The texture height.
     * @param color The initial color.
     * @param format The texture format.
     * @param filtering The texture filtering.
     * @param numMipMaps The number of mip-maps to generate.
     * @return The created texture.
     */
    std::shared_ptr<Texture> createTexture(SizeT width,
                                           SizeT height,
                                           Color color = Color::BLACK,
                                           TextureFormat format = Texture::DefaultTextureFormat,
                                           TextureFiltering filtering = Texture::DefaultTextureFiltering,
                                           u8 numMipMaps = Texture::DefaultMipMaps
    );

    /**
     * Creates a new frame buffer.
     * @param width The frame buffers initial width.
     * @param height The frame buffers initial height.
     * @param numColorAttachments The number of color attachments.
     * @param hasDepthAttachment Whether this frame buffer has a depth attachment.
     * @param hasStencilAttachment Whether this frame buffer has a stencil attachment.
     * @return The created frame buffer.
     */
    std::shared_ptr<FrameBuffer> createFrameBuffer(SizeT width,
                                                   SizeT height,
                                                   u8 numColorAttachments = 1,
                                                   bool hasDepthAttachment = true,
                                                   bool hasStencilAttachment = false);

    /**
     * Creates a new set of shader variables.
     * @param definition The shader variables definition.
     * @return The created shader variables.
     */
    std::shared_ptr<ShaderVariables> createShaderVariables(const ShaderVariablesLayout& definition);

    /**
     * Creates a new vertex buffer.
     * @param numVertices The number of vertices in this buffer.
     * @param layout The vertex attribute layout of this buffer.
     * @return The created vertex buffer.
     */
    std::shared_ptr<VertexBuffer> createVertexBuffer(SizeT numVertices,
                                                     const VertexAttributeLayout& layout);

};

} /* namespace brew */

#endif //BREW_VIDEOCONTEXT_H
