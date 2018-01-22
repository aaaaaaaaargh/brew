/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 02.01.18
 *
 */

#include <brew/video/gl/GLGPUExecutionContext.h>
#include <brew/video/gl/GLExtensions.h>
#include <brew/video/gl/GLMesh.h>
#include <brew/video/gl/GLShaderProgram.h>
#include <brew/video/gl/GLShaderVariables.h>
#include <brew/video/gl/GLIndexBuffer.h>

#include <brew/video/VideoContext.h>

namespace brew {

using gl = GL31;

void GLGPUExecutionContext::renderElement(const RenderTarget& target, const Renderable& renderable, const Viewport& viewport) {
    // Bind the VAO.
    auto& mesh = static_cast<GLMeshContextHandle&>(*renderable.mesh->getMesh());
    mesh.bind();

    // Update the camera.
    viewport.getCamera().update();

    // Bind the shader and uniform buffer.
    if(renderable.shaderProgram) {
        auto& shaderProgram = static_cast<GLShaderProgramContextHandle&>(**renderable.shaderProgram);
        shaderProgram.bind();

        if(renderable.shaderVariables) {
            try {
                // Try to set the built-in variables. This will throw an exception in case this set does not contain any
                // built-in variable.
                const brew::Matrix4& combinedCam = viewport.getCamera().getCombinedMatrix();
                renderable.shaderVariables->set(ShaderVariables::BuiltInCombinedCameraMatrix, combinedCam);
                renderable.shaderVariables->set(ShaderVariables::BuiltInWorldTransformMatrix, renderable.worldTransform);
            } catch(const InvalidArgumentException&) {}

            auto& shaderVariables = static_cast<GLShaderVariablesContextHandle&>(**renderable.shaderVariables);
            auto& context = target.getContext();

            GLuint bindingPoint = 1;

            auto blockIndex = gl::glGetUniformBlockIndex(shaderProgram.getGLId(), "vars");
            gl::glUniformBlockBinding(shaderProgram.getGLId(), blockIndex, bindingPoint);

            // Sync the shader variables before binding to apply the engine vars.
            shaderVariables.syncToGPU(*renderable.shaderVariables);

            shaderVariables.bind(shaderProgram);
            gl::glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, shaderVariables.getGLId());
        }
    }

    // Bind the index buffer.
    auto &ibo = static_cast<GLIndexBufferContextHandle&>(*renderable.mesh->getMesh().getIndices());
    ibo.bind();

    // Apply the viewport.
    if(mesh.getGLState().currentViewport != &viewport) {
        mesh.getGLState().currentViewport = &viewport;

        glViewport(
                static_cast<GLint>(viewport.getPhysicalX()),
                static_cast<GLint>(viewport.getPhysicalY()),
                static_cast<GLsizei>(viewport.getPhysicalWidth()),
                static_cast<GLsizei>(viewport.getPhysicalHeight())
        );

        // Todo: Calculate screen offsets.

        /*glScissor(
                static_cast<GLint>(viewport.getPhysicalX()),
                static_cast<GLint>(viewport.getPhysicalY()),
                static_cast<GLsizei>(viewport.getPhysicalWidth()),
                static_cast<GLsizei>(viewport.getPhysicalHeight())
        );*/

        glEnable(GL_SCISSOR_TEST);

        glClear(GL_COLOR_BUFFER_BIT);
    }

    glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(renderable.mesh->getNumIndices()),
            GL_UNSIGNED_SHORT,   // type must match IndexBuffer::index_type
            nullptr
    );

    if(renderable.shaderProgram) {
        auto& shaderProgram = static_cast<GLShaderProgramContextHandle&>(**renderable.shaderProgram);
        shaderProgram.unbind();

        if(renderable.shaderVariables) {
            auto& shaderVariables = static_cast<GLShaderVariablesContextHandle&>(**renderable.shaderVariables);
            shaderVariables.unbind();
        }
    }

    ibo.unbind();
    mesh.unbind();
}

} /* namespace brew */