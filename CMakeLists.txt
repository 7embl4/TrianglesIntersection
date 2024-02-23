cmake_minimum_required (VERSION 3.11)
project ("TrianglesIntersection")
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

#including SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# set application sources
set(source_files
    "src/Application.cpp" 
    "src/Figures.cpp" 
    "src/Interface.cpp"
    "include/Figures.h"
    "include/Interface.h"
)

# add application executable
add_executable (TrianglesIntersection ${source_files})
target_link_libraries(TrianglesIntersection PRIVATE sfml-graphics)

# including gtest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# set tests sources
set(test_files
    "tests/main.cpp"
)

# add tests executable
add_executable(tests ${test_files})
target_link_libraries(tests PRIVATE sfml-graphics gtest gtest_main)
