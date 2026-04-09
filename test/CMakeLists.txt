###################################################
#
#
# Lastmodified:
#
###################################################

# Matライブラリのテスト
enable_testing()

# テストの追加
add_executable(mat_tests mat_tests.cpp)
add_executable(randstream_tests test_randstream.cpp)

# 必要なライブラリのリンク
target_link_libraries(mat_tests PRIVATE mat gtest::gtest gtest::main)
target_link_libraries(randstream_tests PRIVATE mat gtest::gtest gtest::main)

# インクルードディレクトリの設定
target_include_directories(mat_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/mat)
target_include_directories(randstream_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/mat)

# テストの登録
include(GoogleTest)
gtest_discover_tests(mat_tests)
gtest_discover_tests(randstream_tests)