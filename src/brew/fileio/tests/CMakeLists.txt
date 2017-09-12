cmake_minimum_required(VERSION 3.6)

brew_add_test(VFS vfs.cpp)
brew_link_test_libraries(BrewFileIO)
