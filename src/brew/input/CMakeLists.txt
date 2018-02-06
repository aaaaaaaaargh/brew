##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

project(BrewInput)

brew_library(Input
		InputDevice.cpp
		InputManager.cpp
		KeySym.cpp
)

add_subdirectory(linux)

#add_subdirectory(tests)