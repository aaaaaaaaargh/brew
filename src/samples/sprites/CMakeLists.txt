cmake_minimum_required(VERSION 3.6)

project(SpritesSample)

set(SRCS
        "SpritesSample.cpp"
        )

set(BREW_SAMPLE_VFS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("SampleConfig.h.in" "SampleConfig.h")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(BREW REQUIRED COMPONENTS VideoLinux CoreProcessors)

include_directories(${BREW_INCLUDE_DIRS})

add_executable(SpritesSample ${SRCS})

target_link_libraries(SpritesSample ${BREW_LIBRARIES})