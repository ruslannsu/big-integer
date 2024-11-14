cmake_minimum_required(VERSION 3.29)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/BigInt)

include_directories(lib/BigInt/include)

add_executable(my_executable src/main.cpp)

target_link_libraries(my_executable BigInt)
