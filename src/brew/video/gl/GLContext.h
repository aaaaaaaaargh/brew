/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 06.09.17
 *
 */

#ifndef BREW_GLCONTEXT_H
#define BREW_GLCONTEXT_H

#include <brew/video/VideoContext.h>
#include <brew/video/gl/GLStateInfo.h>

namespace brew {

class GLContext : public VideoContext {
public:
    /**
     * Creates the context and initializes the GL extensions.
     */
    GLContext();

protected:
    /**
     * Creates a frame buffer handle.
     * @param frameBuffer The frame buffer instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<FrameBufferContextHandle> createObject(FrameBuffer& frameBuffer) override;

    /**
     * Creates a texture handle.
     * @param frameBuffer The texture instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<TextureContextHandle> createObject(Texture& texture) override;

    /**
     * Creates a shader variables handle.
     * @param shaderVariables The shader variables instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<ShaderVariablesContextHandle> createObject(ShaderVariables& shaderVariables) override;

    /**
     * Updates a shader variables handle.
     * @param shaderVariables The shader variables instance.
     */
    void updateObject(ShaderVariables& shaderVariables) override;

    /**
     * Creates a vertex buffer handle.
     * @param vertexBuffer The vertex buffer instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<VertexBufferContextHandle> createObject(VertexBuffer& vertexBuffer) override;

    /**
     * Updates a vertex buffer. Syncs from or to the GPU.
     * @param vertexBuffer The vertex buffer instance.
     */
    void updateObject(VertexBuffer& vertexBuffer) override;

    /**
    * Creates an index buffer handle.
    * @param indexBuffer The index buffer instance.
    * @return The context handle of the created instance.
    */
    std::unique_ptr<IndexBufferContextHandle> createObject(IndexBuffer& indexBuffer) override;

    /**
     * Updates an index buffer. Syncs from or to the GPU.
     * @param indexBuffer The index buffer instance.
     */
    void updateObject(IndexBuffer& indexBuffer) override;

    /**
     * Creates a mesh buffer handle.
     * @param mesh The mesh instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<MeshContextHandle> createObject(Mesh& mesh) override;

    /**
     * Creates a shader handle.
     * @param shader The shader instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<ShaderContextHandle> createObject(Shader& shader) override;

    /**
     * Creates a shader program handle.
     * @param shaderProgram The shader program instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<ShaderProgramContextHandle> createObject(ShaderProgram& shaderProgram) override;

public:
    /**
	 * @return The current state of GL.
	 */
    inline GLStateInfo& getStateInfo() {
        return glStateInfo;
    }

    /**
	 * @return The current state of GL.
	 */
    inline const GLStateInfo& getStateInfo() const {
        return glStateInfo;
    }

public:
    static String getUniformDeclarations(const std::shared_ptr<ShaderVariables>& vars);

public:
    /**
     * Executes a set of GPU operations. For OpenGL this is a blocking operation.
     * @param callback The callback to execute.
     * @param syncToFrame Whether to sync the callback to the current frame. This cannot be unset in OpenGL.
     */
    void execute(ExecuteCallback callback, bool syncToFrame = true) override;


private:
    GLStateInfo glStateInfo;
};

} /* namespace brew */

#endif //BREW_GLCONTEXT_H
