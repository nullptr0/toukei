cmake_minimum_required (VERSION 3.5)
project (Toukei)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra -pedantic")

add_subdirectory (libtoukei)
add_subdirectory (toukei-cli)
