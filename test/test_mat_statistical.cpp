#include <gtest/gtest.h>
#include "../src/mat/mat.h"

TEST(MatStatisticalTest, MeanBasic) {
    // 行ベクトルの平均
    Mat rowVec = {{1.0, 2.0, 3.0, 4.0, 5.0}};
    Mat meanAll = rowVec.mean(); // 全要素の平均
    EXPECT_DOUBLE_EQ(meanAll(0, 0), 3.0);
    
    Mat meanDim0 = rowVec.mean(0); // 行方向（列ごとの平均）
    EXPECT_EQ(meanDim0.rows(), 1);
    EXPECT_EQ(meanDim0.cols(), 5);
    EXPECT_DOUBLE_EQ(meanDim0(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(meanDim0(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(meanDim0(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(meanDim0(0, 3), 4.0);
    EXPECT_DOUBLE_EQ(meanDim0(0, 4), 5.0);
    
    Mat meanDim1 = rowVec.mean(1); // 列方向（行ごとの平均）
    EXPECT_EQ(meanDim1.rows(), 1);
    EXPECT_EQ(meanDim1.cols(), 1);
    EXPECT_DOUBLE_EQ(meanDim1(0, 0), 3.0);
}

TEST(MatStatisticalTest, MeanMatrix) {
    // 行列の平均
    Mat mat = {{1.0, 2.0, 3.0},
               {4.0, 5.0, 6.0}};
    
    // 全要素の平均: (1+2+3+4+5+6)/6 = 3.5
    Mat meanAll = mat.mean();
    EXPECT_DOUBLE_EQ(meanAll(0, 0), 3.5);
    
    // 行方向の平均（各列の平均）: [ (1+4)/2, (2+5)/2, (3+6)/2 ] = [2.5, 3.5, 4.5]
    Mat meanDim0 = mat.mean(0);
    EXPECT_EQ(meanDim0.rows(), 1);
    EXPECT_EQ(meanDim0.cols(), 3);
    EXPECT_DOUBLE_EQ(meanDim0(0, 0), 2.5);
    EXPECT_DOUBLE_EQ(meanDim0(0, 1), 3.5);
    EXPECT_DOUBLE_EQ(meanDim0(0, 2), 4.5);
    
    // 列方向の平均（各行の平均）: [ (1+2+3)/3, (4+5+6)/3 ] = [2.0, 5.0]
    Mat meanDim1 = mat.mean(1);
    EXPECT_EQ(meanDim1.rows(), 2);
    EXPECT_EQ(meanDim1.cols(), 1);
    EXPECT_DOUBLE_EQ(meanDim1(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(meanDim1(1, 0), 5.0);
}

TEST(MatStatisticalTest, StdBasic) {
    // 標準偏差のテスト
    Mat vec = {{1.0, 2.0, 3.0, 4.0, 5.0}};
    Mat stdAll = vec.std(); // 全要素の標準偏差
    // 標準偏差 = sqrt(((1-3)^2+(2-3)^2+(3-3)^2+(4-3)^2+(5-3)^2)/5) = sqrt(10/5) = sqrt(2) ≈ 1.414
    EXPECT_NEAR(stdAll(0, 0), 1.41421356, 1e-5);
}

TEST(MatStatisticalTest, SumBasic) {
    // 合計のテスト
    Mat vec = {{1.0, 2.0, 3.0, 4.0, 5.0}};
    Mat sumAll = vec.sum(); // 全要素の合計
    EXPECT_DOUBLE_EQ(sumAll(0, 0), 15.0);
    
    Mat mat = {{1.0, 2.0, 3.0},
               {4.0, 5.0, 6.0}};
    Mat sumAllMat = mat.sum(); // 全要素の合計
    EXPECT_DOUBLE_EQ(sumAllMat(0, 0), 21.0);
    
    // 行方向の合計（各列の合計）: [1+4, 2+5, 3+6] = [5, 7, 9]
    Mat sumDim0 = mat.sum(0);
    EXPECT_EQ(sumDim0.rows(), 1);
    EXPECT_EQ(sumDim0.cols(), 3);
    EXPECT_DOUBLE_EQ(sumDim0(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(sumDim0(0, 1), 7.0);
    EXPECT_DOUBLE_EQ(sumDim0(0, 2), 9.0);
    
    // 列方向の合計（各行の合計）: [1+2+3, 4+5+6] = [6, 15]
    Mat sumDim1 = mat.sum(1);
    EXPECT_EQ(sumDim1.rows(), 2);
    EXPECT_EQ(sumDim1.cols(), 1);
    EXPECT_DOUBLE_EQ(sumDim1(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(sumDim1(1, 0), 15.0);
}