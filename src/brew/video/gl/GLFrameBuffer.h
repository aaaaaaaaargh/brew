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

#ifndef BREW_GLFRAMEBUFFER_H
#define BREW_GLFRAMEBUFFER_H

#include <brew/video/FrameBuffer.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

/**
 * GL implementation of the frame buffer context handle.
 */
class GLFrameBufferContextHandle : public FrameBufferContextHandle, public GLObject {
public:
    /**
     * Creates a new frame buffer context handle.
     * @param frameBuffer The frame buffer instance.
     * @throws RuntimeException in case there was an error creating the frame buffer.
     */
    GLFrameBufferContextHandle(GLContext& context, const FrameBuffer& frameBuffer);

    /**
     * Destructor.
     */
    virtual ~GLFrameBufferContextHandle();

public:
    /**
     * Binds the frame buffer.
     */
    void bind();

    /**
     * Unbinds the frame buffer.
     */
    void unbind();

private:
    std::vector<GLenum> drawBuffers;
};

} /* namespace brew */

#endif //BREW_GLFRAMEBUFFER_H
