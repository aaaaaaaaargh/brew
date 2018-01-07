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

#ifndef BREW_FRAMEBUFFER_H
#define BREW_FRAMEBUFFER_H

#include <brew/core/ProxyObjectManager.h>
#include <brew/video/Texture.h>

namespace brew {

class VideoContext;

/**
 * The video context handle of a frame buffer. Implementation is driver specific.
 */
class FrameBufferContextHandle {};

/**
 * A class for handling frame buffers.
 */
class FrameBuffer : public ProxyObject<FrameBufferContextHandle> {
public:
    /**
     * Creates a new frame buffer.
     * @param videoContext The video context.
     * @param width The frame buffers initial width.
     * @param height The frame buffers initial height.
     * @param numColorAttachments The number of color attachments.
     * @param hasDepthAttachment Whether this frame buffer has a depth attachment.
     * @param hasStencilAttachment Whether this frame buffer has a stencil attachment.
     */
    FrameBuffer(VideoContext& videoContext,
                SizeT width,
                SizeT height,
                u8 numColorAttachments,
                bool hasDepthAttachment,
                bool hasStencilAttachment);

public:
    /**
     * @return The width of the frame buffer.
     */
    inline SizeT getWidth() const {
        return width;
    }

    /**
     * @return The height of the frame buffer.
     */
    inline SizeT getHeight() const {
        return height;
    }

    /**
     * @return The number of color attachments.
     */
    inline u8 getNumColorAttachments() const {
        return static_cast<u8>(colorTextures.size());
    }

    /**
     * @return Whether the frame buffer has a depth attachment.
     */
    inline bool hasDepthAttachment() const {
        return _hasDepthAttachment;
    }

    /**
     * @return Whether the frame buffer has a stencil attachment.
     */
    inline bool hasStencilAttachment() const {
        return _hasStencilAttachment;
    }

    typedef std::vector<std::reference_wrapper<const Texture> > TextureSet;

    /**
     * @return The color textures of this frame buffer.
     */
    inline const TextureSet& getColorTextures() const {
        return colorTextureRefs;
    }

    /**
     * @return The depth texture, if available.
     * @throws IllegalAccessException if the texture is not available.
     */
    inline const Texture& getDepthTexture() const {
        if(!_hasDepthAttachment) {
            throw IllegalAccessException("This frame buffer does not have depth attachment.");
        }
        return *depthTexture;
    }

    /**
     * @return The stencil texture, if available.
     * @throws IllegalAccessException if the texture is not available.
     */
    inline const Texture& getStencilTexture() const {
        if(!_hasStencilAttachment) {
            throw IllegalAccessException("This frame buffer does not have stencil attachment.");
        }
        return *stencilTexture;
    }

private:
    SizeT width, height;
    bool _hasDepthAttachment;
    bool _hasStencilAttachment;

    std::vector<std::shared_ptr<Texture> > colorTextures;
    std::vector<std::reference_wrapper<const Texture> > colorTextureRefs;
    std::shared_ptr<Texture> depthTexture;
    std::shared_ptr<Texture> stencilTexture;
};

}

#endif //BREW_FRAMEBUFFER_H
