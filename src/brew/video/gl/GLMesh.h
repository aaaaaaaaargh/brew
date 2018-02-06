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

#ifndef BREW_GLMESH_H
#define BREW_GLMESH_H

#include <brew/video/Mesh.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

/**
 * GL implementation of a vertex buffer context handle.
 */
class GLMeshContextHandle : public MeshContextHandle, public GLObject {
public:
    /**
     * Creates a new mesh context handle.
     * @param context The GL context.
     * @param mesh The mesh to create the handle from.
     */
    GLMeshContextHandle(GLContext& context, Mesh& mesh);

    /**
     * Destructor.
     */
    ~GLMeshContextHandle();

public:
    /**
     * Binds the vertex buffer of this mesh.
     */
    void bind();

    /**
     * Unbinds the vertex buffer of this mesh.
     */
    void unbind();
};

} /* namespace brew */

#endif //BREW_GLMESH_H
