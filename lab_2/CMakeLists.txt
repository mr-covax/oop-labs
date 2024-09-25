cmake_minimum_required(VERSION 3.10)
project("Lab 2" VERSION 1.0)

# This project will use C++ 20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Configure header locations
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)
FetchContent_MakeAvailable(gtest)

# Add flags to make Google Test happy
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Create the library for custom Base-6 object
add_library(six src/six.cpp)

# Configure testing
enable_testing()
add_executable(lab_test tests/main.cpp)
target_link_libraries(lab_test gtest six)

# Add tests to the testing batch
add_test(NAME all_tests COMMAND lab_test)