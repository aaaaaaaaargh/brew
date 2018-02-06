##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

project(BrewCore)

brew_library(Core
        AppContext.cpp
        AbstractBuffer.cpp
        Counter.cpp
        Exception.cpp
        HeapBuffer.cpp
        Log.cpp
        Object.cpp
        String.cpp
        StringBuffer.cpp
        SystemInfo.cpp
)

add_subdirectory(tests)