/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Sep 4, 2016
 *
 */

#include <brew/video/Mesh.h>

namespace brew {

Mesh::Mesh(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<IndexBuffer> ib)
: SubMesh(
        *this,
        0,
        ib->getNumIndices()
    ),
  vertexBuffer(std::move(vb)),
  indexBuffer(std::move(ib)) {
}

} /* namespace brew */
