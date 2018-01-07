cmake_minimum_required(VERSION 3.6)

project(SpritesSample)

set(SRCS
        "SpritesSample.cpp"
        )

find_package(BREW REQUIRED COMPONENTS VideoLinux)

include_directories(${BREW_INCLUDE_DIRS})

add_executable(SpritesSample ${SRCS})

target_link_libraries(SpritesSample ${BREW_LIBRARIES})