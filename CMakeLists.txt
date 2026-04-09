###################################################
#
#
# Lastmodified:
#
###################################################
cmake_minimum_required(VERSION 4.0.0)
project(sample VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
message(STATUS "Build " ${PROJECT_NAME})
include(FetchContent)
#
# set(CMAKE_VERBOSE_MAKEFILE TRUE)


add_subdirectory(src)