cmake_minimum_required(VERSION 3.6)

include (cmake/brew.cmake)

brew_init()

add_subdirectory(brew/core)
add_subdirectory(brew/math)
add_subdirectory(brew/fileio)
add_subdirectory(brew/video)
add_subdirectory(brew/asset)
add_subdirectory(brew/state)
add_subdirectory(brew/input)

add_subdirectory(samples)

brew_build_monolithic_library()
brew_build_monolithic_tests()
