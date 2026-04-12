###################################################
#
# Lastmodified:
#
###################################################
cmake_minimum_required(VERSION 4.0.0)
project(test VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
message(STATUS "Build Tests for " ${PROJECT_NAME})

# GoogleTestが見つかることを前提とする
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# テストソースファイル
set(TEST_SOURCES
    test_mat_linspace_range.cpp
    test_mat_statistical.cpp
    test_mat_vector_ops.cpp
    test_mat_basic_ops.cpp
)

# テスト実行可能ファイルを作成
add_executable(runTests ${TEST_SOURCES})

# 必要なライブラリにリンク
target_link_libraries(runTests
    PRIVATE
        ${GTEST_BOTH_LIBRARIES}
        pthread
        mat  # 自身のライブラリ
)

# テストをCTestに追加
include(GoogleTest)
gtest_discover_tests(runTests)