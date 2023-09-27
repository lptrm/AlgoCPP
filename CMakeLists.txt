cmake_minimum_required(VERSION 3.12)

project(Aufgabe_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES A1.cpp)

add_executable(Application ${SOURCES})
