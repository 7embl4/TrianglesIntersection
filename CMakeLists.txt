﻿cmake_minimum_required (VERSION 3.14)
project ("TrianglesIntersection")
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

# including SFML
add_subdirectory(3rdparty/sfml)

set(lib_sources
    "src/Figures.cpp" 
    "src/Algorithm.cpp"
    "include/Figures.h" 
    "include/Algorithm.h"
)

# make library and link sfml to this
add_library(figures-lib STATIC ${lib_sources})
target_link_libraries(figures-lib PUBLIC sfml-graphics)

# set application sources
set(app_files
    "src/Application.cpp"
)

# add application executable and link library
add_executable (TrianglesIntersection ${app_files})
target_link_libraries(TrianglesIntersection PUBLIC figures-lib)

# copy dll's
if(WIN32)
    if(BUILD_SHARED_LIBS)
    add_custom_command(TARGET TrianglesIntersection POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:TrianglesIntersection>)
    endif()
endif()

# if use debug type of build, then build tests for lib as well
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(3rdparty/gtest)
    enable_testing()

    set(test_files
        "test/test.cpp"
    )

    add_executable(triangle_inter_tests ${test_files})
    target_link_libraries(triangle_inter_tests PUBLIC 
        figures-lib 
        sfml-graphics 
        GTest::gtest 
        GTest::gtest_main
    )

    if(WIN32)
        if(BUILD_SHARED_LIBS)
        add_custom_command(TARGET TrianglesIntersection POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:gtest>
                $<TARGET_FILE:gtest_main>
                $<TARGET_FILE_DIR:TrianglesIntersection>)
        endif()
    endif()

    add_test(
        NAME triangle_inter_tests
        COMMAND triangle_inter_tests.exe
    )
endif()
