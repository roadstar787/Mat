# cmake_minimum_required(VERSION 3.10)
project(MatTests CXX)

# C++標準を設定
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContentモジュールの読み込み
include(FetchContent)

# Google Test の取得設定（Git リポジトリから取得）
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest
)
FetchContent_MakeAvailable(googletest)

# ライブラリと実行ファイルの追加
# add_library(mat STATIC
#     ../src/mat/mat.h
# )

# テストの追加
add_executable(test_statistical test_mat_statistical_extended.cpp)
target_link_libraries(test_statistical mat gtest_main)
add_test(NAME test_statistical COMMAND test_statistical)

add_executable(test_advanced test_mat_advanced_functions.cpp)
target_link_libraries(test_advanced mat gtest_main)
add_test(NAME test_advanced COMMAND test_advanced)