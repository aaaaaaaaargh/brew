cmake_minimum_required(VERSION 3.6)

project(BrewInput)

brew_library(Input
		InputDevice.cpp
		InputManager.cpp
		KeySym.cpp
)

add_subdirectory(linux)

#add_subdirectory(tests)