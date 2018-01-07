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

#include <brew/video/gl/GLFrameBuffer.h>
#include <brew/video/gl/GLExtensions.h>
#include <brew/video/gl/GLTexture.h>

namespace brew {

using gl = GL30;

GLFrameBufferContextHandle::GLFrameBufferContextHandle(GLContext& context, const FrameBuffer& frameBuffer)
: GLObject(context) {
    glId = 0;

    gl::glGenFramebuffers(1, &glId);
    bind();

    SizeT i = 0;

    drawBuffers.clear();

    for (auto& texPtr : frameBuffer.getColorTextures()) {
        auto& tex = static_cast<GLTextureContextHandle&>(*texPtr.get());
        drawBuffers.push_back(static_cast<unsigned int&&>(GL_COLOR_ATTACHMENT0 + i));
        gl::glFramebufferTexture2D(GL_FRAMEBUFFER, drawBuffers.back(), GL_TEXTURE_2D, tex.getGLId(), 0);
        i++;
    }

    if(frameBuffer.hasDepthAttachment()) {
        // Create the depth buffer texture.
        auto& tex = static_cast<GLTextureContextHandle&>(*frameBuffer.getDepthTexture());
        gl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.getGLId(), 0);
    }

    gl::glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), &drawBuffers[0]);

    switch (gl::glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
        case GL_FRAMEBUFFER_UNDEFINED:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_UNDEFINED");
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
        case GL_FRAMEBUFFER_UNSUPPORTED:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_UNSUPPORTED");
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            throw RuntimeException("Error creating framebuffer: GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
    }
}

void GLFrameBufferContextHandle::bind() {
    gl::glBindFramebuffer(GL_FRAMEBUFFER, glId);
    gl::glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), &drawBuffers[0]);
}

void GLFrameBufferContextHandle::unbind() {
    gl::glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLFrameBufferContextHandle::~GLFrameBufferContextHandle() {
    gl::glDeleteFramebuffers(1, &glId);
}

} /* namespace brew */
