cmake_minimum_required(VERSION 3.12.0)
project(StiltFox_Universal_Library VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT SFSkipTesting)
    find_package(GTest)
    include(GoogleTest)
endif ()