###################################################
#
#
# Lastmodified:
#
###################################################
include(FetchContent)

# Eigenの追加（ヘッダーオンリー） - 別のURLを試す
FetchContent_Declare(
    eigen
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip
    URL_HASH SHA256=9901b3c8d6d4a3689a9b9c1b9e1b9c1b9e1b9c1b9e1b9c1b9e1b9c1b9e1b9c1b9e1
)

FetchContent_MakeAvailable(eigen)

# Eigenをヘッダーオンリーとしてインクルードディレクトリを設定
set_target_properties(eigen PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${eigen_SOURCE_DIR}"
)

# googletestの追加 - 最新の安定版URLを使用
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
    URL_HASH SHA256=2ea296f11d075e5f42d2b40b8f604b24c9c5b8edbf0a9031d3382a5fadc1b77
)

FetchContent_MakeAvailable(googletest)