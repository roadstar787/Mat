# Mat

MATLAB風EigenラッパーAPI

## 概要

Matは、C++の数値計算ライブラリEigen（バージョン3.4.0）を基盤とし、MATLABに近い直感的なシンタックスで行列演算を行うためのラッパークラスです。

## 主な機能

### 基本行列演算
- **四則演算**: `+`, `-`, スカラー `*`, `/`
- **行列積**: `mtimes()`
- **要素ごとの積**: `times()`

### 行列操作
- **転置行列**: `transpose()`
- **逆行列**: `inverse()`
- **行列式**: `determinant()`
- **単位行列生成**: `eye()`
- **水平連結**: `horizontalConcat()`
- **垂直連結**: `verticalConcat()`
- **部分行列スライス**: `slice()`

### 静的メソッド
- **ゼロ行列**: `zeros()`
- **1行列**: `ones()`
- **差分計算**: `diff()`
- **移動平均**: `movmean()`
- **逆正接**: `atan2()`

### 乱数生成
- **一様乱数**: `rand()`, `randn()`
- **乱数の種設定**: `setRandomSeed()`

## インストール

### 依存関係
- CMake 3.0以上
- C++11対応コンパイラ
- Eigen 3.4.0以上

### ビルド方法

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## APIリファレンス

### コンストラクタ

```cpp
// デフォルトコンストラクタ (0x0行列)
Mat mat;

// サイズ指定コンストラクタ
Mat mat(3, 4);  // 3x4のゼロ行列

// 初期化リスト
Mat mat = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
```

### 基本プロパティ

```cpp
int rows = mat.rows();    // 行数取得
int cols = mat.cols();    // 列数取得
int numel = mat.numel();  // 要素数取得
```

### 要素アクセス

```cpp
double value = mat(0, 0);    // 要素取得 (0-based)
mat(0, 0) = 1.0;            // 要素代入 (0-based)
double linear = mat(5);     // 線形インデックスでのアクセス
```

### 基本演算

```cpp
Mat result = mat1 + mat2;    // 行列加算
Mat result = mat1 - mat2;    // 行列減算
Mat result = mat * 2.0;      // スカラー乗算
Mat result = mat / 2.0;      // スカラー除算

Mat result = mat1.mtimes(mat2);  // 行列積 (線形代数)
Mat result = mat1.times(mat2);   // 要素ごとの積 (アダマール積)
```

### 行列操作

```cpp
Mat transposed = mat.transpose();      // 転置行列
Mat inverse = mat.inverse();           // 逆行列
double det = mat.determinant();        // 行列式

Mat squareEye = Mat::eye(3);           // 3x3単位行列
Mat rectEye = Mat::eye(2, 4);          // 2x4単位行列

Mat hconcat = mat1.horizontalConcat(mat2);  // 水平連結
Mat vconcat = mat1.verticalConcat(mat2);    // 垂直連結

Mat submatrix = mat.slice(0, 1, 2, 2);     // 部行列取得
```

### 静的メソッド

```cpp
Mat zeroMat = Mat::zeros(3, 4);        // 3x4ゼロ行列
Mat onesMat = Mat::ones(3, 4);         // 3x4の1行列
Mat diffMat = Mat::diff(inputMat);     // 隣接要素の差分
Mat meanMat = Mat::movmean(inputMat, 5); // 移動平均
Mat atanMat = Mat::atan2(Y, X);        // 4象限逆正接
```

### 乱数生成

```cpp
Mat randomMat = rand(3, 4);           // 3x4の一様乱数 [0,1)
Mat randomMat = rand(2, 3, -1.0, 1.0); // 2x3の範囲指定一様乱数 [-1.0,1.0)
Mat normalMat = randn(3, 3);           // 3x3の正規乱数 N(0,1)

setRandomSeed(12345);                  // 乱数の種を設定
unsigned int seed = getRandomSeed();   // 現在の乱数の種を取得
```

### 表示

```cpp
mat.disp();           // 行列をコンソールに表示
mat.disp("Matrix A"); // ラベル付きで表示
```

## 使用例

### 基本的な行列演算

```cpp
#include "mat.h"

int main() {
    // 行列の作成
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = {{5.0, 6.0}, {7.0, 8.0}};
    
    // 行列演算
    Mat sum = a + b;
    Mat product = a.mtimes(b);
    Mat elementwise = a.times(b);
    
    // 行列操作
    Mat transposed = a.transpose();
    double det = a.determinant();
    Mat inverse = a.inverse();
    
    // 単位行列の作成
    Mat eye3 = Mat::eye(3);
    
    // 連結操作
    Mat hconcat = a.horizontalConcat(b);
    
    // 表示
    a.disp("Matrix A");
    sum.disp("Sum");
    
    return 0;
}
```

### 乱数生成の使用例

```cpp
#include "mat.h"

int main() {
    // 一様乱数の生成
    Mat uniformRand = rand(3, 4);
    uniformRand.disp("Uniform Random Matrix [0,1)");
    
    // 指定範囲の一様乱数の生成
    Mat rangeRand = rand(2, 3, -5.0, 5.0);
    rangeRand.disp("Random Matrix [-5.0,5.0)");
    
    // 正規乱数の生成
    Mat normalRand = randn(5, 1);
    normalRand.disp("Normal Random Vector N(0,1)");
    
    // 乱数の種を設定して再現性を確保
    setRandomSeed(42);
    Mat reproducible1 = rand(2, 2);
    
    setRandomSeed(42);
    Mat reproducible2 = rand(2, 2);
    
    // 同じ乱数列が生成されることを確認
    reproducible1.disp("Reproducible 1");
    reproducible2.disp("Reproducible 2");
    
    return 0;
}
```

### 高度な使用例

```cpp
#include "mat.h"

int main() {
    // 3x3行列の作成
    Mat mat = {{2.0, 5.0, 3.0}, 
               {1.0, 3.0, 2.0}, 
               {4.0, 1.0, 1.0}};
    
    // 行列式の計算
    double det = mat.determinant();
    std::cout << "Determinant: " << det << std::endl;
    
    // 逆行列の計算と検証
    Mat inv = mat.inverse();
    Mat identity = mat.mtimes(inv);
    std::cout << "Identity matrix:" << std::endl;
    identity.disp();
    
    // 部行列の取得
    Mat sub = mat.slice(0, 1, 2, 2);
    std::cout << "Submatrix:" << std::endl;
    sub.disp();
    
    // 乱数を使った行列の作成
    Mat randomMatrix = rand(3, 3);
    std::cout << "Random matrix:" << std::endl;
    randomMatrix.disp();
    
    return 0;
}
```

## テスト

```bash
cd build
ctest
```

## ライセンス

[ライセンス情報]

## 更新履歴

### v0.3.0 (2026-04-09)
- 乱数生成機能を追加
- RandStreamクラスを実装
- 一様乱数と正規乱数の生成をサポート
- 乱数の種の管理機能を追加
- クロスプラットフォーム対応の乱数生成を実装
- 乱数生成のテストケースを追加

### v0.2.0 (2026-04-09)
- 転置行列メソッドを追加
- 逆行列メソッドを追加
- 行列式メソッドを追加
- 単位行列生成メソッドを追加
- 水平・垂直連結メソッドを追加
- 部分行列スライスメソッドを追加
- 各メソッドのテストケースを追加

### v0.1.0
- 初期リリース