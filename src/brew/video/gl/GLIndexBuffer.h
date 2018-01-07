/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 13.09.17
 *
 */

#ifndef BREW_GLINDEXBUFFER_H
#define BREW_GLINDEXBUFFER_H

#include <brew/video/IndexBuffer.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

/**
 * GL implementation of a vertex buffer context handle.
 */
class GLIndexBufferContextHandle : public IndexBufferContextHandle, public GLObject {
public:
    /**
     * Creates a new index buffer handle.
     * @param context The GL context.
     * @param indexBuffer The index buffer to create the handle from.
     */
    GLIndexBufferContextHandle(GLContext& context, IndexBuffer& indexBuffer);

    /**
     * Destructor.
     */
    ~GLIndexBufferContextHandle();

public:
    /**
     * Syncs the contents of an index buffer to the GPU.
     * @param indexBuffer The index buffer.
     */
    void sync(IndexBuffer& indexBuffer);

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

#endif //BREW_GLINDEXBUFFER_H
