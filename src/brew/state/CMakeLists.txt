##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

project(BrewState)

brew_library(State
        State.cpp
        StateSequence.cpp
)

add_subdirectory(tests)
