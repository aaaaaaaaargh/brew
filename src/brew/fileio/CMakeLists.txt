cmake_minimum_required(VERSION 3.2)

project(BrewFileIO)

brew_library(FileIO
		FileStream.cpp
		VirtualFileSystem.cpp
		HeapFileSystem.cpp
		LocalFileSystem.cpp
		)

add_subdirectory(tests)




