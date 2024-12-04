cmake_minimum_required(VERSION 3.10)

project("OOP Lab 7" VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fsanitize=address -pedantic -Werror=maybe-uninitialized")

include_directories(include)

add_subdirectory(src/npc)
add_subdirectory(src/factories)

add_executable(Main main.cpp)
target_link_libraries(Main NPC Factories)