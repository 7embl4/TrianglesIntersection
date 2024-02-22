cmake_minimum_required (VERSION 3.11)

project ("TrianglesIntersection")

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(source_files
    "src/Application.cpp" 
    "src/Figures.cpp" 
    "src/Interface.cpp"
    "src/Algorithm.cpp"
    "include/Figures.h"
    "include/Interface.h"
    "include/Algorithm.h"
)

add_executable (TrianglesIntersection ${source_files})
target_link_libraries(TrianglesIntersection PRIVATE sfml-graphics)
