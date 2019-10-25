cmake_minimum_required(VERSION 3.0)
project(purple)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(APP_NAME "purple")


include_directories(includes)

set(SOURCES
	src/main.cpp
	src/config.cpp
	src/purple.cpp
	src/utils.cpp
)

set(HEADER_FILES
	includes/config.hpp
	includes/purple.hpp
	includes/utils.hpp
)
add_executable(purple ${SOURCES} ${HEADER_FILES})

