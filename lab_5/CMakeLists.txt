cmake_minimum_required(VERSION 3.10)

project("OOP Lab 5" VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -pedantic -fsanitize=address -Werror=maybe-uninitialized")

include_directories(include)

# Download and build Google Test
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)
FetchContent_MakeAvailable(gtest)

add_library(BlockAllocator src/block_allocator.cpp)

add_executable(Main src/main.cpp)
target_link_libraries(Main BlockAllocator)

add_executable(StackTest tests/stack.cpp)
target_link_libraries(StackTest BlockAllocator gtest)
add_test(NAME StackTest COMMAND stack_test)

add_executable(AllocatorTest tests/block_allocator.cpp)
target_link_libraries(AllocatorTest BlockAllocator gtest)
add_test(NAME AllocatorTest COMMAND test_stack)

