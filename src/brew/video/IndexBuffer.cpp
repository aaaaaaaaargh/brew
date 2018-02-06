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

#include <brew/video/IndexBuffer.h>

namespace brew {

IndexBuffer::IndexBuffer(index_type numIndices)
: GPUBuffer(numIndices * sizeof(index_type)), numIndices(numIndices) {

}

void IndexBuffer::write(IndexBuffer::index_type index, IndexBuffer::index_type vertex) {
    GPUBuffer::write(&vertex, index * sizeof(index_type));
}

IndexBuffer::index_type IndexBuffer::read(IndexBuffer::index_type index) const {
    index_type result;
    GPUBuffer::read(&result, index * sizeof(index_type));
    return result;
}

} /* namespace brew */