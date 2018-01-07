cmake_minimum_required(VERSION 3.6)

project(BrewAsset)

brew_library(Asset
        AssetManager.cpp
)

add_subdirectory(tests)
