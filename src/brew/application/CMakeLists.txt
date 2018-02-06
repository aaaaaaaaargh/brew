##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

project(BrewApplication)

brew_library(Application
        Application.cpp
)

add_subdirectory(linux)
add_subdirectory(android)

# add_subdirectory(tests)
