##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

# Options for the build system configuration.
option(BREW_BUILD_MONOLITHIC "Create a monolithic build of BREW" ON)
option(BREW_BUILD_STATIC_LIBRARY "Create static libraries instead of shared ones" OFF)

# Initializes the build system. Sets input and target directories as well as global macros.
# This macro is usually called once before anything else in the build process happens.
macro(brew_init)
    # Set the flag indicating that this is a BREW build.
    set_property(GLOBAL PROPERTY _THIS_IS_A_BREW_BUILD 1)

    # Detect the BREW include directory.
    get_filename_component(BREW_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
    set(BREW_INCLUDE_DIR "${BREW_INCLUDE_DIR}" CACHE INTERNAL "")

    # Detect the library output directory.
    set(BREW_OUTPUT_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

    set(BREW_OUTPUT_LIB_DIR "${BREW_OUTPUT_LIB_DIR}" CACHE INTERNAL "")

    # Detect the executable output directory.
    set(BREW_OUTPUT_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(BREW_OUTPUT_BIN_DIR "${BREW_OUTPUT_BIN_DIR}" CACHE INTERNAL "")

    # Give a build system summary.
    message(STATUS "BREW include set to ${BREW_INCLUDE_DIR}")
    message(STATUS "BREW libraries will be written to ${BREW_OUTPUT_LIB_DIR}")
    message(STATUS "BREW executables will be written to ${BREW_OUTPUT_BIN_DIR}")
    if(BREW_BUILD_MONOLITHIC)
      message(STATUS "BREW will be built as a monolithic library.")
    else()
      message(STATUS "BREW will be built in multiple component libraries.")
    endif()

    if(BREW_BUILD_STATIC_LIBRARY)
      message(STATUS "BREW libraries will be static.")
    else()
      message(STATUS "BREW libraries will be shared.")
    endif()
endmacro()

# Configures default settings for BREW components.
macro(brew_configure_project_defaults)
    # Set the debug macro name.
    set(CMAKE_CXX_FLAGS_DEBUG "-DBREW_DEBUG -g")

    # Require C++14 standard
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED on)

    # Enable threads
    find_package(Threads REQUIRED)

    # Enable position independent code.
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

    # The include directory should have been set by brew_init().

    # Set the project library output directory.
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BREW_OUTPUT_LIB_DIR})

    # Set the project executable output directory.
    set(EXECUTABLE_OUTPUT_PATH ${BREW_OUTPUT_BIN_DIR})

    # Add the BREW header directory to the standard includes.
    include_directories(${BREW_INCLUDE_DIR})
endmacro()

# Adds a new library component to the engine.
# It depends on the BREW_BUILD_MONOLITHIC and BREW_BUILD_STATIC_LIBRARY
# what the exact outcome of this macro will be.
# @param name the library name, will be prefixed with "Brew".
macro(brew_library name)
  brew_configure_project_defaults()

  set(target "Brew${name}")

  set(sources "${ARGN}")

  if(BREW_BUILD_MONOLITHIC)
    # Monolithic build
    add_library(${target} OBJECT ${sources})

    message(STATUS "Adding component ${name} to monolithic library.")

    set_property(GLOBAL APPEND PROPERTY
      _BREW_MONOLITHIC_SOURCES
      $<TARGET_OBJECTS:${target}>
    )
  else()
    # Non-monolithic build
    if(BREW_BUILD_STATIC_LIBRARY)
      set(libtype STATIC)
    else()
      set(libtype SHARED)
    endif()

    add_library(${target} ${libtype} ${sources})
    target_link_libraries(${target} Threads::Threads)
  endif()
endmacro()

macro(brew_link_libraries)
    set(libs "${ARGN}")

    if(BREW_BUILD_MONOLITHIC)
        # Non-monolithic build
        set_property(GLOBAL APPEND PROPERTY
                _BREW_MONOLITHIC_LIBS
                ${libs}
                )
    else()
        # Non-monolithic build
        target_link_libraries(${PROJECT_NAME} ${libs})
    endif()
endmacro()

# Builds the monolithic library. Only produces an output
# if BREW_BUILD_MONOLITHIC is enabled.
macro(brew_build_monolithic_library)
  if(BREW_BUILD_MONOLITHIC)
    project(BrewMonolithic)
      brew_configure_project_defaults()

      get_property(sources GLOBAL PROPERTY _BREW_MONOLITHIC_SOURCES)
      get_property(libs GLOBAL PROPERTY _BREW_MONOLITHIC_LIBS)

      if(BREW_BUILD_STATIC_LIBRARY)
        set(libtype STATIC)
      else()
        set(libtype SHARED)
      endif()

      add_library(Brew ${libtype} ${sources})

      if(libs)
          target_link_libraries(Brew ${libs})
      endif()
  endif()
endmacro()

include(cmake/brew_test.cmake)
