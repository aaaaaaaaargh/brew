/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 25.04.17
 *
 */

#include <brew/video/SubMesh.h>

namespace brew {

SubMesh::SubMesh(Mesh& mesh, SizeT indexOffset, SizeT numIndices)
        : mesh(mesh),
          indexOffset(indexOffset),
          numIndices(numIndices) {

}

} /* namespace brew */