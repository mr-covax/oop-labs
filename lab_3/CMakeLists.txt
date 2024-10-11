cmake_minimum_required(VERSION 3.10)
project("Lab 3" VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pedantic -fsanitize=address -Werror=maybe-uninitialized")

include_directories(${PROJECT_SOURCE_DIR}/include)

# Pull and build Google Test
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)
FetchContent_MakeAvailable(gtest)

# The definition of the Shapes library
add_library(
    figures
    src/base/polygon.cpp
    src/base/container.cpp
    src/shapes/triangle.cpp
    src/shapes/hexagon.cpp
    src/shapes/octagon.cpp
)

# Executables
add_executable(main src/main.cpp)
target_link_libraries(main figures)

add_executable(triangleTest tests/triangle.cpp)
target_link_libraries(triangleTest figures gtest)

# Testing configuration
enable_testing()
add_test(NAME TRIANGLE_SUITE COMMAND triangleTest)