cmake_minimum_required(VERSION 3.8)
project(GPB)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp A*/linkedList.cpp A*/linkedList.h A*/routeNode.cpp A*/routeNode.h)
add_executable(GPB ${SOURCE_FILES})