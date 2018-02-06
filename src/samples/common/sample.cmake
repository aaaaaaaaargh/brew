##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

set(BREW_SAMPLE_VFS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("../common/SampleConfig.h.in" "SampleConfig.h")
include_directories(${CMAKE_CURRENT_BINARY_DIR})