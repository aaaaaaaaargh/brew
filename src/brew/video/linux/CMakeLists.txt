cmake_minimum_required(VERSION 3.6)

find_package(X11 QUIET)
if(X11_FOUND)

project(BrewVideoLinux)

brew_library(VideoLinux
		GLXCanvas.cpp
		X11Canvas.cpp
		)

#add_subdirectory(tests)

endif()
