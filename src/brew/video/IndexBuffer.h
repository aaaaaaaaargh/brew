/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 12.09.17
 *
 */

#ifndef BREW_INDEXBUFFER_H
#define BREW_INDEXBUFFER_H

#include <brew/video/VertexAttributeLayout.h>
#include <brew/video/GPUBuffer.h>

namespace brew {

/**
 * The video context handle of an index buffer. Implementation is driver specific.
 */
class IndexBufferContextHandle : public GPUBufferContextHandle {
protected:
    using GPUBufferContextHandle::getGPUBufferUpdateData;
};

/**
 * A class representing index buffers that are uploaded to GPU memory.
 */
class IndexBuffer : public GPUBuffer<IndexBufferContextHandle> {
public:
    typedef u16 index_type;

public:
    /**
     * Creates a new index buffer.
     * @param numIndices The number of indices for this buffer.
     */
    explicit IndexBuffer(index_type numIndices);

public:
    /**
     * Writes an index.
     * @param index The index.
     * @param vertex The vertex.
     */
    void write(index_type index, index_type vertex);

    /**
     * Reads an index.
     * @param index The index.
     * @return The vertex index.
     */
    index_type read(index_type index) const;

public:
    /**
     * @return The number of indices in this buffer.
     */
    inline SizeT getNumIndices() const {
        return numIndices;
    }

    /**
     * @return The context handle of this instance.
     */
    inline IndexBufferContextHandle& getContextHandle() {
        return getObject();
    }

private:
    SizeT numIndices;
};

} /* namespace brew */

#endif //BREW_INDEXBUFFER_H
