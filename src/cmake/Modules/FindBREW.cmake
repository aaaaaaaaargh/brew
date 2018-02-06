##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

# - Try to find BREW.
# Usage: find_package(BREW REQUIRED [COMPONENTS component1 component2])
# Once done this will define
#  BREW_FOUND - System has BREW
#  BREW_INCLUDE_DIRS - The BREW include directories
#  BREW_LIBRARIES - The libraries needed to use BREW
#  BREW_DEFINITIONS - Compiler switches required for using BREW

cmake_minimum_required(VERSION 3.6)

function(_brew_get_component_dependencies component ret)
    # Define all component dependencies.
    set(_BREW_CORE_DEPENDENCIES "")
    set(_BREW_MATH_DEPENDENCIES Core)
    set(_BREW_FILEIO_DEPENDENCIES Core)
    set(_BREW_VIDEO_DEPENDENCIES Core Math)
    set(_BREW_VIDEOGL_DEPENDENCIES Video)
    set(_BREW_VIDEOLINUX_DEPENDENCIES VideoGL)
    set(_BREW_ASSETS_DEPENDENCIES Core FileIO)
    set(_BREW_COREASSETPROCESSORS_DEPENDENCIES Video Assets)
    set(_BREW_STATE_DEPENDENCIES Core)
    set(_BREW_INPUT_DEPENDENCIES Core)
    set(_BREW_INPUTLINUX_DEPENDENCIES Input VideoLinux)

    set(_BREW_APPLICATION_DEPENDENCIES Core Math Video FileIO Assets Input)
    set(_BREW_APPLICATIONLINUX_DEPENDENCIES Application InputLinux VideoLinux)
    set(_BREW_APPLICATIONANDROID_DEPENDENCIES Application)

    string(TOUPPER ${component} icomponent)

    set(localdeps ${_BREW_${icomponent}_DEPENDENCIES})
    set(result ${component} ${localdeps})

    foreach(dep IN LISTS localdeps)
        _brew_get_component_dependencies(${dep} thisret)
        list(APPEND result ${thisret})
    endforeach()

    if(result)
        list(REMOVE_DUPLICATES result)
    endif()

    set(${ret} ${result} PARENT_SCOPE)
endfunction()

function(_brew_get_all_component_dependencies ret)
    foreach(component IN LISTS BREW_FIND_COMPONENTS)
        _brew_get_component_dependencies(${component} thisret)
        list(APPEND result ${thisret})
    endforeach()

    if(result)
        list(REMOVE_DUPLICATES result)
    endif()

    set(${ret} ${result} PARENT_SCOPE)
endfunction()

_brew_get_all_component_dependencies(deps)
message("-- Required BREW components: ${deps}")

find_path(BREW_INCLUDE_DIR brew/core/Object.h
        HINTS ${CMAKE_SOURCE_DIR/src}
        PATH_SUFFIXES brew )

find_path(BREW_INCLUDE_DIR brew/core/Object.h
        HINTS ${CMAKE_SOURCE_DIR/src}
        PATH_SUFFIXES brew )

get_property(IS_BREW_BUILD GLOBAL PROPERTY _THIS_IS_A_BREW_BUILD)

if(IS_BREW_BUILD)
    if(BREW_BUILD_MONOLITHIC)
        set(BREW_INCLUDE_DIRS ${BREW_INCLUDE_DIR})
        set(BREW_LIBRARIES "Brew")
    else()
        foreach(dep IN LISTS deps)
            list(APPEND BREW_LIBRARIES "Brew${dep}")
        endforeach()
    endif()
else()
    # NOT IMPLEMENTED YET.
    #find_library(BREW_LIBRARY NAMES Brew)
endif()

find_package(Threads REQUIRED)
set(BREW_LIBRARIES ${BREW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
set(BREW_DEFINITIONS ${BREW_DEFINITIONS} "-pthread")

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set BREW_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(BREW  DEFAULT_MSG
        BREW_LIBRARIES BREW_INCLUDE_DIR BREW_DEFINITIONS)

mark_as_advanced(BREW_INCLUDE_DIR BREW_LIBRARY )
