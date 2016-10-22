cmake_minimum_required(VERSION 2.8.12.2)

project(fractals)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

# include directories
include_directories(
	.
	..
	../include
)

# library directories
link_directories(
)


# files to compile
file(GLOB_RECURSE SRC_FILES
    "*.h"
    "*.cpp"
)


add_executable(fractals ${SRC_FILES})

target_link_libraries(fractals
	Qt5::Widgets
)
