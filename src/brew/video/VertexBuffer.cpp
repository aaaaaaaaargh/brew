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

#include <brew/video/VertexBuffer.h>

namespace brew {

VertexBuffer::VertexBuffer(SizeT numVertices, const VertexAttributeLayout& layout)
: GPUBuffer(numVertices * layout.getSize()), layout(layout), numVertices(numVertices) {

}

} /* namespace brew */