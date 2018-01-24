cmake_minimum_required(VERSION 3.6)

project(BrewVideo)

brew_library(Video
        BitmapFont.cpp
        Camera.cpp
        Color.cpp
        ExtendViewport.cpp
        Font.cpp
        FrameBuffer.cpp
        Frustum.cpp
        GPUBuffer.cpp
        GPUExecutionContext.cpp
        IndexBuffer.cpp
        Mesh.cpp
        NativeViewport.cpp
        OrthoCamera.cpp
        PerspectiveCamera.cpp
        Pixmap.cpp
        PixmapAtlas.cpp
        RenderBatch.cpp
        RenderSettings.cpp
        RenderTarget.cpp
        ScalingViewport.cpp
        Shader.cpp
        ShaderProgram.cpp
        ShaderVariables.cpp
        SubMesh.cpp
        Texture.cpp
        TextureAtlas.cpp
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
