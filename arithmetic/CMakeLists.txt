cmake_minimum_required(VERSION 3.7)
project(arithmetic)
file(GLOB SOURCES "*.cpp")
set(CMAKE_BUILD_TYPE Debug)
include_directories(../stack ../unit-test-framework)
add_executable(arithmetic ${SOURCES})
