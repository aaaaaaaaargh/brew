/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 06.09.17
 *
 */

#include <brew/video/gl/GLContext.h>
#include <brew/video/gl/GLFrameBuffer.h>
#include <brew/video/gl/GLTexture.h>
#include <brew/video/gl/GLShaderVariables.h>
#include <brew/video/gl/GLExtensions.h>
#include <brew/video/gl/GLVertexBuffer.h>
#include <brew/video/gl/GLIndexBuffer.h>
#include <brew/video/gl/GLMesh.h>
#include <brew/video/gl/GLShader.h>
#include <brew/video/gl/GLShaderProgram.h>

#include <brew/video/gl/GLGPUExecutionContext.h>

namespace brew {

GLContext::GLContext() {
    GLExtensions::init();
}

std::unique_ptr<FrameBufferContextHandle> GLContext::createObject(FrameBuffer& frameBuffer) {
    return std::make_unique<GLFrameBufferContextHandle>(*this, frameBuffer);
}

std::unique_ptr<TextureContextHandle> GLContext::createObject(Texture& texture) {
    return std::make_unique<GLTextureContextHandle>(*this, texture);
}

std::unique_ptr<ShaderVariablesContextHandle> GLContext::createObject(ShaderVariables& shaderVariables) {
    return std::make_unique<GLShaderVariablesContextHandle>(*this, shaderVariables);
}

void GLContext::updateObject(ShaderVariables& shaderVariables) {
    auto& handle = static_cast<GLShaderVariablesContextHandle&>(*shaderVariables);
    handle.syncToGPU(shaderVariables, false);
}

std::unique_ptr<VertexBufferContextHandle> GLContext::createObject(VertexBuffer& vertexBuffer) {
    return std::make_unique<GLVertexBufferContextHandle>(*this, vertexBuffer);
}

void GLContext::updateObject(VertexBuffer& vertexBuffer) {
    auto& handle = static_cast<GLVertexBufferContextHandle&>(*vertexBuffer);
    handle.sync(vertexBuffer);
}

std::unique_ptr<IndexBufferContextHandle> GLContext::createObject(IndexBuffer& indexBuffer) {
    return std::make_unique<GLIndexBufferContextHandle>(*this, indexBuffer);
}

void GLContext::updateObject(IndexBuffer& indexBuffer) {
    auto& handle = static_cast<GLIndexBufferContextHandle&>(*indexBuffer);
    handle.sync(indexBuffer);
}

std::unique_ptr<MeshContextHandle> GLContext::createObject(Mesh& mesh) {
    return std::make_unique<GLMeshContextHandle>(*this, mesh);
}

std::unique_ptr<ShaderContextHandle> GLContext::createObject(Shader& shader) {
    return std::make_unique<GLShaderContextHandle>(*this, shader);
}

std::unique_ptr<ShaderProgramContextHandle> GLContext::createObject(ShaderProgram& shaderProgram) {
    return std::make_unique<GLShaderProgramContextHandle>(*this, shaderProgram);
}

void GLContext::execute(VideoContext::ExecuteCallback callback, bool syncToFrame) {
    GLGPUExecutionContext ctx(*this);
    callback(ctx);
}

String GLContext::getUniformDeclarations(const std::shared_ptr<ShaderVariables>& vars) {
    return GLShaderVariablesContextHandle::generateUniformDeclarationSource(vars->getDefinition());
}

String GLContext::getUniformDeclarations(const ShaderVariablesLayout& vars) {
    return GLShaderVariablesContextHandle::generateUniformDeclarationSource(vars);
}

} /* namespace brew */
