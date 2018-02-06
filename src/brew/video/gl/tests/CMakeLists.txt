##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

brew_add_test(GLContext GLContextTest.cpp)
brew_add_test(GLFrameBuffer FrameBuffer.cpp)
brew_add_test(GLShaders Shaders.cpp)
brew_add_test(GLVertexBuffer VertexBuffer.cpp)
brew_add_test(GLIndexBuffer IndexBuffer.cpp)
brew_add_test(GLMesh Mesh.cpp)

