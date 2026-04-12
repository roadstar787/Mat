###################################################
#
#
# Lastmodified:
#
###################################################

# FetchContentモジュールの読み込み
include(FetchContent)
#  eignegの検索とダウンロード

# Eigen 3.4.0 の取得設定
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG        3.4.0
  GIT_SHALLOW    TRUE
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/eigen
)
FetchContent_MakeAvailable(eigen)



# Matライブラリの作成
add_library(mat mat.cpp randstream.cpp)

# Eigenをヘッダーオンリーとして使用
# Eigenのインクルードディレクトリを直接指定
target_include_directories(mat PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${eigen_SOURCE_DIR}
)

# Eigenのリンクは不要（ヘッダーオンリーのため）
# target_link_libraries(mat PRIVATE Eigen3::Eigen)
# (removed stray character)