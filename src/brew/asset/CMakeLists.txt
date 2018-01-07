cmake_minimum_required(VERSION 3.6)

project(BrewAsset)

brew_library(Asset
        AbstractAssetManager.cpp
        AssetPipeline.cpp
        AssetProcessor.cpp
        AssetPromise.cpp
)

add_subdirectory(tests)
