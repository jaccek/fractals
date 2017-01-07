cmake_minimum_required(VERSION 2.8.11)

project(qttest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

add_executable(qttest main.cpp)

target_link_libraries(qttest Qt5::Widgets ${CMAKE_DL_LIBS})
