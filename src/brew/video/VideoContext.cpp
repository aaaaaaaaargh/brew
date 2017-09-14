/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 04.09.17
 *
 */

#include <brew/video/VideoContext.h>

namespace brew {

void VideoContext::processPendingOperations() {
    ProxyObjectManager<Texture, TextureContextHandle>::processAllObjects();
    ProxyObjectManager<FrameBuffer, FrameBufferContextHandle>::processAllObjects();
    ProxyObjectManager<ShaderVariables, ShaderVariablesContextHandle>::processAllObjects();
    ProxyObjectManager<VertexBuffer, VertexBufferContextHandle>::processAllObjects();
    ProxyObjectManager<IndexBuffer, IndexBufferContextHandle>::processAllObjects();
    ProxyObjectManager<Mesh, MeshContextHandle>::processAllObjects();
}

std::shared_ptr<Texture> VideoContext::createTexture(SizeT width,
                                                     SizeT height,
                                                     Color color,
                                                     TextureFormat format,
                                                     TextureFiltering filtering,
                                                     u8 numMipMaps) {
    return ProxyObjectManager<Texture, TextureContextHandle>::allocateObject(
            width, height, color, format, filtering, numMipMaps
    );
}

std::shared_ptr<FrameBuffer>
VideoContext::createFrameBuffer(SizeT width, SizeT height, u8 numColorAttachments, bool hasDepthAttachment,
                                bool hasStencilAttachment) {
    return ProxyObjectManager<FrameBuffer, FrameBufferContextHandle>::allocateObject(
            *this, width, height, numColorAttachments, hasDepthAttachment, hasStencilAttachment
    );
}

std::shared_ptr<ShaderVariables> VideoContext::createShaderVariables(const ShaderVariablesLayout& definition) {
    return ProxyObjectManager<ShaderVariables, ShaderVariablesContextHandle>::allocateObject(
            definition
    );
}

std::shared_ptr<VertexBuffer> VideoContext::createVertexBuffer(SizeT numVertices, const VertexAttributeLayout& layout) {
    return ProxyObjectManager<VertexBuffer, VertexBufferContextHandle>::allocateObject(
            numVertices, layout
    );
}

std::shared_ptr<IndexBuffer> VideoContext::createIndexBuffer(SizeT numIndices) {
    return ProxyObjectManager<IndexBuffer, IndexBufferContextHandle>::allocateObject(
            numIndices
    );
}

std::shared_ptr<Mesh> VideoContext::createMesh(std::shared_ptr<VertexBuffer> vertexBuffer,
                                               std::shared_ptr<IndexBuffer> indexBuffer) {
    return ProxyObjectManager<Mesh, MeshContextHandle>::allocateObject(
            vertexBuffer, indexBuffer
    );
}

} /* namespace brew */