###################################################
#
#
# Lastmodified:
#
###################################################

# FetchContentモジュールの読み込み
cmake_minimum_required(VERSION 3.14)
project(Mat)

include(FetchContent)
#  eignegの検索とダウンロード

# Eigen 3.4.0 の取得設定
set(BUILD_TESTING OFF CACHE BOOL "Disable tests" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "Disable Eigen tests" FORCE)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "Disable Eigen docs" FORCE)

FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG        3.4.0
  GIT_SHALLOW    TRUE
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/eigen
)
FetchContent_MakeAvailable(eigen)
# Eigen のヘッダーを全てのターゲットで利用可能にする（ライブラリ作成前に設定）
include_directories(${eigen_SOURCE_DIR})

# C++11 を有効化（Eigen が C++11 を要求）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Matライブラリの作成
add_library(mat
    basic_ops.cpp
    statistical.cpp
    linear_algebra.cpp
    utils.cpp
    randstream.cpp
    mat.cpp
)

# Eigenをヘッダーオンリーとして使用
# Eigenのインクルードディレクトリを直接指定
target_include_directories(mat PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${eigen_SOURCE_DIR}
    ${eigen_SOURCE_DIR}/Eigen
)

# Eigenのリンクは不要（ヘッダーオンリーのため）
# target_link_libraries(mat PRIVATE Eigen3::Eigen)
# (removed stray character)