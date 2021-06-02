cmake_minimum_required(VERSION 3.16)
project(first_c)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)

find_package(loguru CONFIG REQUIRED)
target_link_libraries(main PRIVATE loguru)