##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

project(SimpleApplicationSample)

include(../common/sample.cmake)

set(SRCS
        main.cpp
        )

# This is how BREW can be included in your project.
find_package(BREW REQUIRED COMPONENTS VideoLinux CoreProcessors)

include_directories(${BREW_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${BREW_LIBRARIES})