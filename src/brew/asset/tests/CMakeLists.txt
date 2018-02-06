##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

brew_add_test(AssetManager AssetManager.cpp)

brew_add_test(AssetBundle AssetBundle.cpp)

brew_link_test_libraries(BrewAsset)


