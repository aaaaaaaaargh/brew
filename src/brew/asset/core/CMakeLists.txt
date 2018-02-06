##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

project(BrewCoreAssetProcessors)

brew_library(CoreAssetProcessors
        BitmapFontProcessor.cpp
        CoreAssetProcessors.cpp
        JSONProcessor.cpp
        PixmapProcessor.cpp
        TextureAtlasProcessor.cpp
        TextureProcessor.cpp
)

