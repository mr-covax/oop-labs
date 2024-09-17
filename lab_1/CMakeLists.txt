cmake_minimum_required(VERSION 3.10)
project("Lab 1" VERSION 1.0)

# Enable the C++20 standard for this project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Setup include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# To make Google Test happy:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Google Test framework
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)
FetchContent_MakeAvailable(gtest)

# Our main library
add_library(divider src/divider.cpp)

# Configure testing
enable_testing()
add_executable(lab_test tests/test.cpp)
target_link_libraries(lab_test divider gtest)

# Main executable definition and configuration
add_executable(lab src/main.cpp)
target_link_libraries(lab divider)

# Add tests to the testing batch
add_test(NAME LAB_TESTING COMMAND lab_test)
