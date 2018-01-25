cmake_minimum_required(VERSION 3.6)

project(BrewVideoGL)

brew_library(VideoGL
		GLCanvas.cpp
		GLContext.cpp
		GLGPUExecutionContext.cpp
		GLExtensions.cpp
		GLFrameBuffer.cpp
		GLIndexBuffer.cpp
		GLMesh.cpp
		GLObject.cpp
		GLShader.cpp
		GLShaderProgram.cpp
		GLShaderVariables.cpp
		GLTexture.cpp
		GLVertexBuffer.cpp
		)

brew_link_libraries(GL)

# add_subdirectory(tests) # TODO: Fix the tests.
