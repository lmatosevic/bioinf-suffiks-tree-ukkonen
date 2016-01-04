cmake_minimum_required(VERSION 3.3)
project(bioinf_suffiks_tree_ukkonen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(bioinf_suffiks_tree_ukkonen ${SOURCE_FILES})