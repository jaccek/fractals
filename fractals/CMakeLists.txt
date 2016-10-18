cmake_minimum_required(VERSION 2.8.12.2)

project(fractals)

# include directories
include_directories(
	.
	..
	../include
)

# library directories
link_directories(
	../artefacts
	../lib/SFML
)


# files to compile
file(GLOB_RECURSE SRC_FILES
    "*.h"
    "*.cpp"
)


add_executable(fractals ${SRC_FILES})

target_link_libraries(fractals
	sfml-graphics
	sfml-window
	sfml-system
)
