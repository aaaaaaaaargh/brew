cmake_minimum_required(VERSION 3.6)

# Options for the build system configuration.
option(BREW_BUILD_TESTS "Build the engine test fixtures." ON)
option(BREW_BUILD_MONOLITHIC_TESTS "Create a single target for all unit tests." ON)

# Adds a new test target for BREW.
# @param name The name of the test, will be prefixed with "Test_".
macro(brew_add_test name)
    if(BREW_BUILD_TESTS)
        find_package(GTest QUIET)
        set(target "Test_${name}")

        project(${target})

        brew_configure_project_defaults()

        set(sources "${ARGN}")

        if(BREW_BUILD_MONOLITHIC_TESTS)
            add_library(${target} OBJECT ${sources})

            set_property(GLOBAL APPEND PROPERTY
                    _BREW_MONOLITHIC_TESTS_SOURCES
                    $<TARGET_OBJECTS:${target}>
                    )
        else()
            add_executable(${target} ${libtype} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/TestsMain.cpp ${sources})

            if(BREW_BUILD_MONOLITHIC)
                target_link_libraries(${target} Brew)
            endif()

            target_link_libraries(${target} ${GTEST_BOTH_LIBRARIES} Threads::Threads)

            enable_testing()
            add_test(${name} ${target})
        endif()
    endif()
endmacro()

# Links additional libraries to the current test target.
macro(brew_link_test_libraries)
    if(BREW_BUILD_TESTS)
        set(libs "${ARGN}")
        if(BREW_BUILD_MONOLITHIC_TESTS)
            set_property(GLOBAL APPEND PROPERTY
                    _BREW_MONOLITHIC_TESTS_LIBS
                    ${libs}
                    )
        else()
            list(FILTER libs EXCLUDE REGEX "Brew.*")
            if(libs)
                target_link_libraries(${PROJECT_NAME} ${libs})
            endif()
        endif()
    endif()
endmacro()

# Builds the monolithic tests executable. Only produces an output
# if BREW_BUILD_MONOLITHIC_TESTS is enabled.
macro(brew_build_monolithic_tests)
    if(BREW_BUILD_TESTS)
        find_package(GTest REQUIRED)

        if(BREW_BUILD_MONOLITHIC_TESTS)
            project(BrewMonolithicTests)
            brew_configure_project_defaults()

            get_property(sources GLOBAL PROPERTY _BREW_MONOLITHIC_TESTS_SOURCES)
            get_property(libs GLOBAL PROPERTY _BREW_MONOLITHIC_TESTS_LIBS)

            set(target BrewUnitTests)

            add_executable(${target} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/TestsMain.cpp ${sources})

            if(BREW_BUILD_MONOLITHIC)
                target_link_libraries(${target} Brew)
            endif()

            list(FILTER libs EXCLUDE REGEX "Brew.*")
            if(libs)
                target_link_libraries(${target} ${libs})
            endif()

            target_link_libraries(${target} ${GTEST_BOTH_LIBRARIES} Threads::Threads)

            enable_testing()
            add_test(AllTests ${target})
        endif()
    endif()
endmacro()