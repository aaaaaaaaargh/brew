##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.2)

project(BrewFileIO)

brew_library(FileIO
		FileStream.cpp
		VirtualFileSystem.cpp
		HeapFileSystem.cpp
		LocalFileSystem.cpp
		)

add_subdirectory(tests)




