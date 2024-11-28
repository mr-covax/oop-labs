cmake_minimum_required(VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)
FetchContent_MakeAvailable(gtest)

add_executable(TestSuite main.cpp factory.cpp npc.cpp)
target_link_libraries(TestSuite gtest NPC Factories)