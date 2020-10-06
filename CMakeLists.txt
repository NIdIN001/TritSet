cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 20)
add_executable(lab1 main.cpp TritSet.cpp)


add_subdirectory(googletest)
include_directories(googletest/googletest/include)
target_link_libraries(lab1 gtest gtest_main)

