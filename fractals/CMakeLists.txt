cmake_minimum_required(VERSION 2.8.12.2)

project(fractals)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# include directories
include_directories(
	.
	..
	../include
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
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
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
)

file(COPY
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/base.vert
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/base.frag
	DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../artifacts/shaders
)
