##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

project(BrewMath)

brew_library(Math
        BoundingBox.cpp
        Math.cpp
        Matrix4.cpp
        Plane.cpp
        Quaternion.cpp
        Scale2D.cpp
        Vec2.cpp
        Vec3.cpp
        Vec4.cpp
)

add_subdirectory(tests)
