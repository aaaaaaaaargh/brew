/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 12.09.17
 *
 */

#ifndef BREW_VERTEXBUFFER_H
#define BREW_VERTEXBUFFER_H

#include <brew/video/VertexAttributeLayout.h>
#include <brew/video/GPUBuffer.h>

namespace brew {

/**
 * The video context handle of a vertex buffer. Implementation is driver specific.
 */
class VertexBufferContextHandle : public GPUBufferContextHandle {
protected:
    using GPUBufferContextHandle::getGPUBufferUpdateData;
};

/**
 * A class representing vertex buffers that are uploaded to GPU memory.
 */
class VertexBuffer : public GPUBuffer<VertexBufferContextHandle> {
public:
    /**
     * Creates a new vertex buffer.
     * @param numVertices The number of vertices.
     * @param layout The attribute layout.
     */
    VertexBuffer(SizeT numVertices, const VertexAttributeLayout& layout);

public:
    /**
     * Writes a vertex attribute.
     * @tparam Attrib The attribute type.
     * @param index The vertex index.
     * @param value The new value.
     * @param nth An optional attribute index if there are multiple attributes of the given type.
     */
    template<typename Attrib>
    void write(SizeT index, const typename Attrib::value_type& value, SizeT nth=0) {
        SizeT offset = index * layout.getSize() + layout.getAttributeOffset<Attrib>(nth);
        Attrib::write(value, *this, offset);
    }

    /**
     * Reads a vertex attribute.
     * @tparam Attrib The attribute type.
     * @param index The vertex index.
     * @param nth An optional attribute index if there are multiple attributes of the given type.
     * @return The value.
     */
    template<typename Attrib>
    typename Attrib::value_type read(SizeT index, SizeT nth=0) const {
        SizeT offset = index * layout.getSize() + layout.getAttributeOffset<Attrib>(nth);
        return Attrib::read(*this, offset);
    }

public:
    /**
     * @return The vertex layout of this buffer.
     */
    inline const VertexAttributeLayout& getLayout() const {
        return layout;
    }

    /**
     * @return The number of vertices in this buffer.
     */
    inline SizeT getNumVertices() const {
        return numVertices;
    }

    /**
     * @return The context handle of this instance.
     */
    inline VertexBufferContextHandle& getContextHandle() {
        return getObject();
    }

private:
    VertexAttributeLayout layout;
    SizeT numVertices;
};

} /* namespace brew */

#endif //BREW_VERTEXBUFFER_H
