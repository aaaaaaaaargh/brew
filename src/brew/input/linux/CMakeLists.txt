cmake_minimum_required(VERSION 3.6)

find_package(X11 QUIET)
if(X11_FOUND)

project(BrewInputLinux)

brew_library(InputLinux
		X11InputManager.cpp
    )

endif()