cmake_minimum_required(VERSION 3.6)

project(BrewMath)

brew_library(Math
        BoundingBox.cpp
        Math.cpp
        Matrix4.cpp
        Plane.cpp
        Quaternion.cpp
        Vec2.cpp
        Vec3.cpp
        Vec4.cpp
)

add_subdirectory(tests)
