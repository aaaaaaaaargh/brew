cmake_minimum_required(VERSION 3.6)

project(BrewMath)

brew_library(Math
        Math.cpp
        Matrix4.cpp
        Quaternion.cpp
        Vec2.cpp
        Vec3.cpp
        Vec4.cpp
)

add_subdirectory(tests)
