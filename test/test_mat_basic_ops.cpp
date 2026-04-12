#include <gtest/gtest.h>
#include "../src/mat/mat.h"

TEST(MatBasicOpsTest, Constructors) {
    // デフォルトコンストラクタ
    Mat m1;
    EXPECT_EQ(m1.rows(), 0);
    EXPECT_EQ(m1.cols(), 0);
    
    // サイズ指定コンストラクタ
    Mat m2(3, 4);
    EXPECT_EQ(m2.rows(), 3);
    EXPECT_EQ(m2.cols(), 4);
    // すべての要素が0であることを確認
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(m2(i, j), 0.0);
        }
    }
    
    // 初期化リストコンストラクタ
    Mat m3 = {{1.0, 2.0}, {3.0, 4.0}};
    EXPECT_EQ(m3.rows(), 2);
    EXPECT_EQ(m3.cols(), 2);
    EXPECT_DOUBLE_EQ(m3(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m3(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m3(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(m3(1, 1), 4.0);
}

TEST(MatBasicOpsTest, ElementAccess) {
    Mat m = {{1.0, 2.0, 3.0},
             {4.0, 5.0, 6.0}};
    
    // 要素へのアクセス
    EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(m(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(m(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(m(1, 2), 6.0);
    
    // 要素の変更
    m(0, 0) = 10.0;
    EXPECT_DOUBLE_EQ(m(0, 0), 10.0);
    
    // 線形インデックス
    EXPECT_DOUBLE_EQ(m(0), 10.0); // 0番目
    EXPECT_DOUBLE_EQ(m(1), 4.0);  // 1番目（列優先）
    EXPECT_DOUBLE_EQ(m(2), 5.0);  // 2番目
    EXPECT_DOUBLE_EQ(m(5), 6.0);  // 5番目
}

TEST(MatBasicOpsTest, BasicArithmetic) {
    Mat m1 = {{1.0, 2.0},
              {3.0, 4.0}};
    Mat m2 = {{2.0, 2.0},
              {2.0, 2.0}};
    
    // 加算
    Mat addResult = m1 + m2;
    EXPECT_DOUBLE_EQ(addResult(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(addResult(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(addResult(1, 0), 5.0);
    EXPECT_DOUBLE_EQ(addResult(1, 1), 6.0);
    
    // 減算
    Mat subResult = m1 - m2;
    EXPECT_DOUBLE_EQ(subResult(0, 0), -1.0);
    EXPECT_DOUBLE_EQ(subResult(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(subResult(1, 0), 1.0);
    EXPECT_DOUBLE_EQ(subResult(1, 1), 2.0);
    
    // スカラー乗算
    Mat scalarMul = m1 * 2.0;
    EXPECT_DOUBLE_EQ(scalarMul(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(scalarMul(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(scalarMul(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(scalarMul(1, 1), 8.0);
    
    // スカラー除算
    Mat scalarDiv = m1 / 2.0;
    EXPECT_DOUBLE_EQ(scalarDiv(0, 0), 0.5);
    EXPECT_DOUBLE_EQ(scalarDiv(0, 1), 1.0);
    EXPECT_DOUBLE_EQ(scalarDiv(1, 0), 1.5);
    EXPECT_DOUBLE_EQ(scalarDiv(1, 1), 2.0);
}

TEST(MatBasicOpsTest, MatrixMultiplication) {
    Mat m1 = {{1.0, 2.0},
              {3.0, 4.0}};
    Mat m2 = {{2.0, 0.0},
              {1.0, 2.0}};
    
    // 通常の行列積
    Mat mmResult = m1.mtimes(m2);
    // [1*2+2*1, 1*0+2*2; 3*2+4*1, 3*0+4*2] = [4, 4; 10, 8]
    EXPECT_DOUBLE_EQ(mmResult(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(mmResult(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(mmResult(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(mmResult(1, 1), 8.0);
    
    // 要素ごとの積
    Mat elemResult = m1.times(m2);
    EXPECT_DOUBLE_EQ(elemResult(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(elemResult(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(elemResult(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(elemResult(1, 1), 8.0);
}

TEST(MatBasicOpsTest, EyeOnesZeros) {
    // 単位行列
    Mat eye3 = Mat::eye(3);
    EXPECT_EQ(eye3.rows(), 3);
    EXPECT_EQ(eye3.cols(), 3);
    EXPECT_DOUBLE_EQ(eye3(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(eye3(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(eye3(0, 2), 0.0);
    EXPECT_DOUBLE_EQ(eye3(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(eye3(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(eye3(1, 2), 0.0);
    EXPECT_DOUBLE_EQ(eye3(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(eye3(2, 1), 0.0);
    EXPECT_DOUBLE_EQ(eye3(2, 2), 1.0);
    
    // 1行列
    Mat ones23 = Mat::ones(2, 3);
    EXPECT_EQ(ones23.rows(), 2);
    EXPECT_EQ(ones23.cols(), 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(ones23(i, j), 1.0);
        }
    }
    
    // 零行列
    Mat zeros23 = Mat::zeros(2, 3);
    EXPECT_EQ(zeros23.rows(), 2);
    EXPECT_EQ(zeros23.cols(), 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(zeros23(i, j), 0.0);
        }
    }
}

TEST(MatBasicOpsTest, Transpose) {
    Mat m = {{1.0, 2.0, 3.0},
             {4.0, 5.0, 6.0}};
    Mat t = m.transpose();
    EXPECT_EQ(t.rows(), 2);
    EXPECT_EQ(t.cols(), 3);
    EXPECT_DOUBLE_EQ(t(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(t(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(t(0, 2), 0.0); // 要素がないため0
    EXPECT_DOUBLE_EQ(t(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(t(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(t(1, 2), 0.0);
    EXPECT_DOUBLE_EQ(t(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(t(2, 1), 6.0);
    EXPECT_DOUBLE_EQ(t(2, 2), 0.0);
}

TEST(MatBasicOpsTest, Slice) {
    Mat m = {{1.0, 2.0, 3.0, 4.0},
             {5.0, 6.0, 7.0, 8.0},
             {9.0, 10.0, 11.0, 12.0}};
    
    // 中央の2x2部分を取得
    Mat slice = m.slice(1, 1, 2, 2);
    EXPECT_EQ(slice.rows(), 2);
    EXPECT_EQ(slice.cols(), 2);
    EXPECT_DOUBLE_EQ(slice(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(slice(0, 1), 7.0);
    EXPECT_DOUBLE_EQ(slice(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(slice(1, 1), 11.0);
}