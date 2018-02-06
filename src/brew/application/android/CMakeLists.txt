##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")

project(BrewApplicationAndroid)

brew_library(ApplicationAndroid
        AndroidApplication.cpp
)

# add_subdirectory(tests)

endif()