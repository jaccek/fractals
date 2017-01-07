cmake_minimum_required(VERSION 2.8.12.2)

set(PROJECT_NAME mode_api)
project(${PROJECT_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../artifacts/modes)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


# include directories
include_directories(
	.
	..
	../include
)

# library directories
# link_directories(
# )


# files to compile
file(GLOB_RECURSE SRC_FILES
    "*.h"
    "*.cpp"
)


add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# target_link_libraries(${PROJECT_NAME}
# )
