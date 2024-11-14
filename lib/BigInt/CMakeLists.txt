cmake_minimum_required(VERSION 3.29)
project(BigInt)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(BigInt src/BigInt.cpp)

add_subdirectory(test)

add_subdirectory(gtest)