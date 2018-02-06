/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 02.01.18
 *
 */

#include <brew/video/gl/GLGPUExecutionContext.h>
#include <brew/video/gl/GLContext.h>
#include <brew/video/gl/GLExtensions.h>
#include <brew/video/gl/GLMesh.h>
#include <brew/video/gl/GLShaderProgram.h>
#include <brew/video/gl/GLShaderVariables.h>
#include <brew/video/gl/GLIndexBuffer.h>

// Undefine some X11 stuff.
#ifdef None
#undef None
#endif

namespace brew {

using gl = GL31;

GLGPUExecutionContext::GLGPUExecutionContext(GLContext& context)
: GPUExecutionContext(context), GLObject(context) {

}


void GLGPUExecutionContext::renderElement(const RenderTarget& target, const Renderable& renderable, const Viewport& viewport, const RenderSettings& settings) {
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

    auto& glStateInfo = getContext().getStateInfo();

    // Apply the viewport.
    glStateInfo.currentViewport = &viewport;

    auto viewportY = static_cast<GLint>(target.getHeight() - viewport.getPhysicalY() - viewport.getPhysicalHeight());

    glViewport(
            static_cast<GLint>(viewport.getPhysicalX()),
            viewportY,
            static_cast<GLsizei>(viewport.getPhysicalWidth()),
            static_cast<GLsizei>(viewport.getPhysicalHeight())
    );

    // Todo: Calculate screen offsets.

    if(!glStateInfo.isScissorTestEnabled) {
        glEnable(GL_SCISSOR_TEST);
        glStateInfo.isScissorTestEnabled = true;
    }

    glScissor(
            static_cast<GLint>(viewport.getPhysicalX()),
            viewportY,
            static_cast<GLsizei>(viewport.getPhysicalWidth()),
            static_cast<GLsizei>(viewport.getPhysicalHeight())
    );

    // Handle blending
    if(settings.blendMode != glStateInfo.blendMode) {
        if(settings.blendMode == RenderSettings::BlendMode::None) {
            glDisable(GL_BLEND);
        } else {
            if(glStateInfo.blendMode == RenderSettings::BlendMode::None) {
                glEnable(GL_BLEND);
            }

            switch(settings.blendMode) {
                case RenderSettings::BlendMode::SourceAlphaToOneMinusSourceAlpha:
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    break;
                default:
                    throw NotSupportedException("Blend mode is not supported.");
            }
        }

        // Update the blend mode state.
        glStateInfo.blendMode = settings.blendMode;
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