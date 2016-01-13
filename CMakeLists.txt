cmake_minimum_required(VERSION 3.3)
project(bioinf_suffiks_tree_ukkonen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Suffix.cpp include/Suffix.h src/Edge.cpp include/Edge.h src/Node.cpp include/Node.h include/Constants.h src/Constants.cpp include/Functions.h src/Functions.cpp include/FASTAFormat.h include/FASTQFormat.h src/FASTAFormat.cpp src/FASTQFormat.cpp)
add_executable(bioinf_suffiks_tree_ukkonen ${SOURCE_FILES})