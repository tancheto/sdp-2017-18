cmake_minimum_required(VERSION 3.7)
project(lists)
file(GLOB SOURCES "*.cpp")
include_directories(../unit-test-framework)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
add_executable(lists ${SOURCES})

