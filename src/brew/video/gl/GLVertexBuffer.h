/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 13.09.17
 *
 */

#ifndef BREW_GLVERTEXBUFFER_H
#define BREW_GLVERTEXBUFFER_H

#include <brew/video/VertexBuffer.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

/**
 * GL implementation of a vertex buffer context handle.
 */
class GLVertexBufferContextHandle : public VertexBufferContextHandle, public GLObject {
public:
    /**
     * Creates a new vertex buffer handle.
     * @param context The GL context.
     * @param vertexBuffer The vertex buffer to create the handle from.
     */
    GLVertexBufferContextHandle(GLContext& context, VertexBuffer& vertexBuffer);

    /**
     * Destructor.
     */
    ~GLVertexBufferContextHandle();

public:
    /**
     * Syncs the contents of a vertex buffer to the GPU.
     * @param vertexBuffer The vertex buffer.
     */
    void sync(VertexBuffer& vertexBuffer);

public:
    /**
     * Binds this buffer.
     */
    void bind();

    /**
     * Unbinds this buffer.
     */
    void unbind();
};

} /* namespace brew */

#endif //BREW_GLVERTEXBUFFER_H
