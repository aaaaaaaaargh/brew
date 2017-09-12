cmake_minimum_required(VERSION 3.6)

project(BrewVideoLinux)

brew_library(VideoLinux
		GLXCanvas.cpp
		X11Canvas.cpp
		)

#add_subdirectory(tests)
