/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 04.09.17
 *
 */

#ifndef BREW_VIDEOCONTEXT_H
#define BREW_VIDEOCONTEXT_H

#include <brew/core/ProxyObjectManager.h>
#include <brew/core/Object.h>

#include <brew/video/GPUExecutionContext.h>
#include <brew/video/Color.h>
#include <brew/video/Texture.h>
#include <brew/video/FrameBuffer.h>
#include <brew/video/ShaderVariables.h>
#include <brew/video/VertexBuffer.h>
#include <brew/video/IndexBuffer.h>
#include <brew/video/Mesh.h>
#include <brew/video/Shader.h>
#include <brew/video/ShaderProgram.h>

#include <brew/video/Renderable.h>
#include <brew/video/RenderTarget.h>

namespace brew {

class VideoContext :
        public Object,
        private ProxyObjectManager<Texture, TextureContextHandle>,
        private ProxyObjectManager<FrameBuffer, FrameBufferContextHandle>,
        private ProxyObjectManager<ShaderVariables, ShaderVariablesContextHandle>,
        private ProxyObjectManager<VertexBuffer, VertexBufferContextHandle>,
        private ProxyObjectManager<IndexBuffer, IndexBufferContextHandle>,
        private ProxyObjectManager<Mesh, MeshContextHandle>,
        private ProxyObjectManager<Shader, ShaderContextHandle>,
        private ProxyObjectManager<ShaderProgram, ShaderProgramContextHandle>
{
public:
    /**
     * Initializes pending context objects. Should not be called manually.
     */
    void processPendingOperations();

public:
    /**
     * Creates a new empty texture.
     * @param width The texture width.
     * @param height The texture height.
     * @param color The initial color.
     * @param format The texture format.
     * @param filtering The texture filtering.
     * @param numMipMaps The number of mip-maps to generate.
     * @return The created texture.
     */
    std::shared_ptr<Texture> createTexture(SizeT width,
                                           SizeT height,
                                           Color color = Color::BLACK,
                                           TextureFormat format = Texture::DefaultTextureFormat,
                                           TextureFiltering filtering = Texture::DefaultTextureFiltering,
                                           u8 numMipMaps = Texture::DefaultMipMaps
    );

    /**
     * Creates a new texture from an existing pixmap.
     * @param pixmap The source pixmap.
     * @param format The texture format.
     * @param filtering The texture filtering.
     * @param numMipMaps The number of mip-maps to generate.
     * @return The created texture.
     */
    std::shared_ptr<Texture> createTexture(std::shared_ptr<Pixmap> pixmap,
                                           TextureFormat format = Texture::DefaultTextureFormat,
                                           TextureFiltering filtering = Texture::DefaultTextureFiltering,
                                           u8 numMipMaps = Texture::DefaultMipMaps
    );

    /**
     * Creates a new texture from an existing pixmap.
     * @param pixmap The source pixmap.
     * @param format The texture format.
     * @param filtering The texture filtering.
     * @param numMipMaps The number of mip-maps to generate.
     * @return The created texture.
     */
    inline std::shared_ptr<Texture> createTexture(const Pixmap& pixmap,
                                           TextureFormat format = Texture::DefaultTextureFormat,
                                           TextureFiltering filtering = Texture::DefaultTextureFiltering,
                                           u8 numMipMaps = Texture::DefaultMipMaps
    ) {
        return createTexture(std::make_shared<Pixmap>(pixmap), format, filtering, numMipMaps);
    }

    /**
     * Creates a new frame buffer.
     * @param width The frame buffers initial width.
     * @param height The frame buffers initial height.
     * @param numColorAttachments The number of color attachments.
     * @param hasDepthAttachment Whether this frame buffer has a depth attachment.
     * @param hasStencilAttachment Whether this frame buffer has a stencil attachment.
     * @return The created frame buffer.
     */
    std::shared_ptr<FrameBuffer> createFrameBuffer(SizeT width,
                                                   SizeT height,
                                                   u8 numColorAttachments = 1,
                                                   bool hasDepthAttachment = true,
                                                   bool hasStencilAttachment = false);

    /**
     * Creates a new set of shader variables.
     * @param definition The shader variables definition.
     * @return The created shader variables.
     */
    std::shared_ptr<ShaderVariables> createShaderVariables(const ShaderVariablesLayout& definition);

    /**
     * Creates a new vertex buffer.
     * @param numVertices The number of vertices in this buffer.
     * @param layout The vertex attribute layout of this buffer.
     * @return The created vertex buffer.
     */
    std::shared_ptr<VertexBuffer> createVertexBuffer(SizeT numVertices,
                                                     const VertexAttributeLayout& layout);

    /**
     * Creates a new index buffer.
     * @param numIndices The number of indices in this buffer.
     * @return The created index buffer.
     */
    std::shared_ptr<IndexBuffer> createIndexBuffer(SizeT numIndices);

    /**
     * Creates a new mesh.
     * @param vertexBuffer The vertex buffer to use for the mesh.
     * @param indexBuffer The index buffer to use for the mesh.
     * @return The created mesh.
     */
    std::shared_ptr<Mesh> createMesh(std::shared_ptr<VertexBuffer> vertexBuffer,
                                     std::shared_ptr<IndexBuffer> indexBuffer);

    /**
     * Creates a new shader that can be linked to a shader program.
     * @param type The shader type.
     * @param shaderSource The shader source.
     * @return The created shader.
     */
    std::shared_ptr<Shader> createShader(ShaderType type, const String& shaderSource);

    /**
     * Creates a new shader program from a set of compiled shaders.
     * @param shaders The shaders to link to the program.
     * @return The created shader program.
     */
    std::shared_ptr<ShaderProgram> createShaderProgram(std::initializer_list<std::shared_ptr<Shader> > shaders);

public:
    /**
     * A callback for GPU execution.
     */
    typedef std::function<void(GPUExecutionContext&)> ExecuteCallback;

    /**
     * Executes a set of GPU operations. Depending on the video backend this could be a blocking or non-blocking operation.
     * @param callback The callback to execute.
     * @param syncToFrame Whether to sync the callback to the current frame.
     *                    This feature can only be used for non-blocking implementations.
     */
    virtual void execute(ExecuteCallback callback, bool syncToFrame = true) = 0;
};

} /* namespace brew */

#endif //BREW_VIDEOCONTEXT_H
