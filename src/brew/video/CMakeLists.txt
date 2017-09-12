cmake_minimum_required(VERSION 3.6)

project(BrewVideo)

brew_library(Video
        Color.cpp
        FrameBuffer.cpp
        Pixmap.cpp
        RenderTarget.cpp
        ShaderVariables.cpp
        Texture.cpp
        VideoCanvas.cpp
        VideoContext.cpp
)

add_subdirectory(linux)
add_subdirectory(gl)

add_subdirectory(tests)
