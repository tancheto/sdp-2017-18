cmake_minimum_required(VERSION 3.7)
project(teststack)
file(GLOB SOURCES "*.cpp")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
include_directories(../unit-test-framework)
add_executable(teststack ${SOURCES})
