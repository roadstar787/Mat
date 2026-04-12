###################################################
#
#
# Lastmodified:
#
###################################################
cmake_minimum_required(VERSION 4.0.0)
project(sample VERSION 0.1)
enable_testing()
 # プロジェクトは C++11 準拠です（テストコードは C++11 でビルド）
 set(CMAKE_CXX_STANDARD 11)
 set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Build " ${PROJECT_NAME})
include(FetchContent)
#
# set(CMAKE_VERBOSE_MAKEFILE TRUE)


add_subdirectory(src)
add_subdirectory(test)