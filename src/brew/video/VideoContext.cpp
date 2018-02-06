/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
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
    ProxyObjectManager<Shader, ShaderContextHandle>::processAllObjects();
    ProxyObjectManager<ShaderProgram, ShaderProgramContextHandle>::processAllObjects();
}

std::shared_ptr<Texture> VideoContext::createTexture(SizeT width,
                                                     SizeT height,
                                                     Color color,
                                                     TextureFormat format,
                                                     TextureFiltering filtering,
                                                     u8 numMipMaps) {
    auto result = ProxyObjectManager<Texture, TextureContextHandle>::allocateObject(
            width, height, color, format, filtering, numMipMaps
    );

    result->context = this;
    return result;
}

std::shared_ptr<Texture> VideoContext::createTexture(std::shared_ptr<Pixmap> pixmap,
                                                     TextureFormat format,
                                                     TextureFiltering filtering,
                                                     u8 numMipMaps) {
    auto result = ProxyObjectManager<Texture, TextureContextHandle>::allocateObject(
            pixmap, format, filtering, numMipMaps
    );

    result->context = this;
    return result;
}

std::shared_ptr<FrameBuffer>
VideoContext::createFrameBuffer(SizeT width, SizeT height, u8 numColorAttachments, bool hasDepthAttachment,
                                bool hasStencilAttachment) {
    auto result = ProxyObjectManager<FrameBuffer, FrameBufferContextHandle>::allocateObject(
            *this, width, height, numColorAttachments, hasDepthAttachment, hasStencilAttachment
    );

    result->context = this;
    return result;
}

std::shared_ptr<ShaderVariables> VideoContext::createShaderVariables(const ShaderVariablesLayout& definition) {
    auto result = ProxyObjectManager<ShaderVariables, ShaderVariablesContextHandle>::allocateObject(
            definition
    );

    result->context = this;
    return result;
}

std::shared_ptr<VertexBuffer> VideoContext::createVertexBuffer(SizeT numVertices, const VertexAttributeLayout& layout) {
    auto result = ProxyObjectManager<VertexBuffer, VertexBufferContextHandle>::allocateObject(
            numVertices, layout
    );

    result->context = this;
    return result;
}

std::shared_ptr<IndexBuffer> VideoContext::createIndexBuffer(SizeT numIndices) {
    auto result = ProxyObjectManager<IndexBuffer, IndexBufferContextHandle>::allocateObject(
            numIndices
    );

    result->context = this;
    return result;
}

std::shared_ptr<Mesh> VideoContext::createMesh(std::shared_ptr<VertexBuffer> vertexBuffer,
                                               std::shared_ptr<IndexBuffer> indexBuffer) {
    auto result = ProxyObjectManager<Mesh, MeshContextHandle>::allocateObject(
            vertexBuffer, indexBuffer
    );

    result->context = this;
    return result;
}

std::shared_ptr<Shader> VideoContext::createShader(ShaderType type, const String& shaderSource) {
    auto result = ProxyObjectManager<Shader, ShaderContextHandle>::allocateObject(
            type, shaderSource
    );

    result->context = this;
    return result;
}

std::shared_ptr<ShaderProgram> VideoContext::createShaderProgram(std::initializer_list<std::shared_ptr<Shader> > shaders) {
    auto result = ProxyObjectManager<ShaderProgram, ShaderProgramContextHandle>::allocateObject(
            shaders
    );

    result->context = this;
    return result;
}

} /* namespace brew */