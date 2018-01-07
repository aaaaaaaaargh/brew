cmake_minimum_required(VERSION 3.6)

project(BrewVideo)

brew_library(Video
        Camera.cpp
        Color.cpp
        FrameBuffer.cpp
        Frustum.cpp
        GPUBuffer.cpp
        GPUExecutionContext.cpp
        IndexBuffer.cpp
        Mesh.cpp
        OrthoCamera.cpp
        PerspectiveCamera.cpp
        Pixmap.cpp
        RenderTarget.cpp
        RenderBatch.cpp
        Shader.cpp
        ShaderProgram.cpp
        ShaderVariables.cpp
        SubMesh.cpp
        Texture.cpp
        VertexAttribute.cpp
        VertexAttributeLayout.cpp
        VertexBuffer.cpp
        VideoCanvas.cpp
        VideoContext.cpp
        Viewport.cpp
)

add_subdirectory(linux)
add_subdirectory(gl)

add_subdirectory(tests)
