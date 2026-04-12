###################################################
#
#
# Lastmodified:
#
###################################################

# Matライブラリの作成
add_library(mat mat.cpp randstream.cpp)

# Eigenへのリンク
target_link_libraries(mat PRIVATE Eigen3::Eigen)

# インクルードディレクトリの設定
target_include_directories(mat PUBLIC 
    ${CMAKE_SOURCE_DIR}/src/externals/eigen-3.4.0
    ${CMAKE_CURRENT_SOURCE_DIR}
)
