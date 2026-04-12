cmake_minimum_required(VERSION 3.10)
project(MatSimpleTests CXX)

# C++標準を設定
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# インクルードディレクトリを追加
include_directories(../../src)

# 簡易テストの実行ファイルを作成（gtestなし）
add_executable(test_simple_no_gtest test_simple_no_gtest.cpp)