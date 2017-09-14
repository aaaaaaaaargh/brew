/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: Sep 4, 2016
 *
 */

#ifndef BREW_SUBMESH_H
#define BREW_SUBMESH_H

#include <brew/core/Types.h>

namespace brew {

class Mesh;

/**
 * A SubMesh is part of a mesh (or the whole mesh itself) that can be used to instantiate or
 * render certain parts of a mesh.
 */
class SubMesh {
public:
    /**
     * Creates a new sub mesh.
     * @param mesh The source mesh.
     * @param indexOffset The index offset in the source mesh.
     * @param numIndices The number of indices of this sub mesh.
     */
    SubMesh(Mesh& mesh, SizeT indexOffset, SizeT numIndices);

    /**
     * @return The number of indices of this sub mesh.
     */
    inline SizeT getNumIndices() const {
        return numIndices;
    }

    /**
     * @return The index offset where this sub mesh begins.
     */
    inline SizeT getIndexOffset() const {
        return indexOffset;
    }

    /**
     * @return The source mesh.
     */
    inline Mesh& getMesh() {
        return mesh;
    }

    /**
     * @return A const reference to the source mesh.
     */
    inline const Mesh& getMesh() const {
        return mesh;
    }

private:
    Mesh& mesh;
    SizeT indexOffset;
    SizeT numIndices;
};

} /* namespace brew */

#endif //BREW_SUBMESH_H
