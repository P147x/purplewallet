cmake_minimum_required(VERSION 3.0)
project(purple)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(APP_NAME "purple")

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

SET(CMAKE_SYSTEM_NAME Darwin)

if(APPLE)
INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)
endif()
include_directories(includes)
set(SOURCES
	src/main.cpp
	src/config.cpp
	src/purple.cpp
	src/utils.cpp
		src/network.cpp
)

set(HEADER_FILES
	includes/config.hpp
	includes/purple.hpp
		includes/network.hpp
		includes/utils.h)


add_executable(purple ${SOURCES} ${HEADER_FILES})
target_link_libraries(purple curl)
target_link_libraries(purple curlpp)
