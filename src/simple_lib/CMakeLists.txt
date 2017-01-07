cmake_minimum_required(VERSION 2.8.11)

project(simplelib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_library(simplelib SHARED main.cpp)
