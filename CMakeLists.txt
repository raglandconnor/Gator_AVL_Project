cmake_minimum_required(VERSION 3.26)
project(Gator_AVL_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(test-unit)

add_executable(Gator_AVL_Project
        src/main.cpp
        test-unit/catch.hpp
        test-unit/test.cpp
        src/AVL.cpp
        src/AVL.h
)
