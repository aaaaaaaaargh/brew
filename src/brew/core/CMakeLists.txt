cmake_minimum_required(VERSION 3.6)

project(BrewCore)

brew_library(Core
        AppContext.cpp
        AbstractBuffer.cpp
        Exception.cpp
        HeapBuffer.cpp
        Log.cpp
        String.cpp
        StringBuffer.cpp
        SystemInfo.cpp
)

add_subdirectory(tests)