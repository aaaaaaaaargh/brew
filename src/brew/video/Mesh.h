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

#ifndef BREW_MESH_H
#define BREW_MESH_H

#include <brew/core/ProxyObjectManager.h>
#include <brew/video/VertexBuffer.h>
#include <brew/video/IndexBuffer.h>
#include <brew/video/SubMesh.h>
#include <brew/video/VideoContextObject.h>

namespace brew {

/**
 * The video context handle of a mesh. Implementation is driver specific.
 */
class MeshContextHandle {};

/**
 * A mesh is a unique set of a vertex and index buffer that together define a structure in 3D space.
 */
class Mesh : public ProxyObject<MeshContextHandle>, public SubMesh, public VideoContextObject {
public:
	/**
	 * Constructs a new mesh.
	 * @param vertexBuffer The vertex buffer of the mesh.
	 * @param indexBuffer The index buffer of the mesh.
	 */
	Mesh(std::shared_ptr<VertexBuffer> vertexBuffer,
		 std::shared_ptr<IndexBuffer> indexBuffer);

public:
	/**
	 * @return The vertex buffer of the mesh.
	 */
	inline VertexBuffer& getVertices() const {
		return *vertexBuffer;
	}

	/**
	 * @return The index buffer of the mesh.
	 */
	inline IndexBuffer& getIndices() const {
		return *indexBuffer;
	}

protected:
	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
};

} /* namespace brew */

#endif /* BREW_MESH_H */
