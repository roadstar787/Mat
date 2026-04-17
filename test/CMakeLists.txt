# cmake_minimum_required(VERSION 3.10)
project(MatTests CXX)

# C++標準を設定
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContentモジュールの読み込み
include(FetchContent)

# Google Test の取得設定（Git リポジトリから取得）
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest
)
FetchContent_MakeAvailable(googletest)

# Matライブラリは親プロジェクトからリンクします
# add_library(mat STATIC
#     ../src/mat/mat.h
#     ../src/mat/mat.cpp
#     ../src/mat/utils.cpp
#     ../src/mat/statistical.cpp
#     ../src/mat/linear_algebra.cpp
# )

# テストの追加
add_executable(test_statistical test_mat_statistical_extended.cpp)
target_link_libraries(test_statistical mat gtest)
add_test(NAME test_statistical COMMAND test_statistical)

add_executable(test_advanced test_mat_advanced_functions.cpp)
target_link_libraries(test_advanced mat gtest)
add_test(NAME test_advanced COMMAND test_advanced)

add_executable(test_basic_ops test_mat_basic_ops.cpp)
target_link_libraries(test_basic_ops mat gtest)
add_test(NAME test_basic_ops COMMAND test_basic_ops)

add_executable(test_linspace test_mat_linspace_range.cpp)
target_link_libraries(test_linspace mat gtest)
add_test(NAME test_linspace COMMAND test_linspace)

add_executable(test_vector_ops test_mat_vector_ops.cpp)
target_link_libraries(test_vector_ops mat gtest)
add_test(NAME test_vector_ops COMMAND test_vector_ops)

add_executable(test_simple test_simple.cpp)
target_link_libraries(test_simple mat)
add_test(NAME test_simple COMMAND test_simple)