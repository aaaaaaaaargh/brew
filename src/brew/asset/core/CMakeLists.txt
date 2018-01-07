cmake_minimum_required(VERSION 3.6)

project(BrewCoreAssetProcessors)

brew_library(CoreAssetProcessors
        CoreAssetProcessors.cpp
        PixmapProcessor.cpp
        TextureProcessor.cpp
)

