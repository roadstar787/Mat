###################################################
#
#
# Lastmodified:
#
###################################################

# Matライブラリの作成
add_library(mat mat.cpp randstream.cpp)

# Eigenへのリンク
target_link_libraries(mat PRIVATE Eigen3::eigen)

# インクルードディレクトリの設定
target_include_directories(mat PUBLIC 
    ${CMAKE_SOURCE_DIR}/src/external/eigen-3.3.9
    ${CMAKE_CURRENT_SOURCE_DIR}
)