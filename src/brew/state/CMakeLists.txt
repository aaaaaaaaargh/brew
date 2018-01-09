cmake_minimum_required(VERSION 3.6)

project(BrewState)

brew_library(State
        State.cpp
        StateSequence.cpp
)

add_subdirectory(tests)
