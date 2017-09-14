cmake_minimum_required(VERSION 3.6)

project(BrewVideo)

brew_library(Video
        Color.cpp
        FrameBuffer.cpp
        GPUBuffer.cpp
        IndexBuffer.cpp
        Mesh.cpp
        Pixmap.cpp
        RenderTarget.cpp
        ShaderVariables.cpp
        SubMesh.cpp
        Texture.cpp
        VertexAttribute.cpp
        VertexAttributeLayout.cpp
        VertexBuffer.cpp
        VideoCanvas.cpp
        VideoContext.cpp
)

add_subdirectory(linux)
add_subdirectory(gl)

add_subdirectory(tests)
