#include "test_common.h"

TEST(MatLinspaceRangeTest, LinspaceBasic) {
    // 基本的なlinspaceテスト
    Mat result = Mat::linspace(0.0, 10.0, 5);
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 5);
    
    // 値の確認: 0, 2.5, 5, 7.5, 10
    EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.5);
    EXPECT_DOUBLE_EQ(result(0, 2), 5.0);
    EXPECT_DOUBLE_EQ(result(0, 3), 7.5);
    EXPECT_DOUBLE_EQ(result(0, 4), 10.0);
}

TEST(MatLinspaceRangeTest, LinspaceSingleElement) {
    // 要素数1の場合
    Mat result = Mat::linspace(5.0, 5.0, 1);
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_DOUBLE_EQ(result(0, 0), 5.0);
}

TEST(MatLinspaceRangeTest, LinspaceZeroElements) {
    // 要素数0以下の場合
    Mat result = Mat::linspace(0.0, 10.0, 0);
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 0);
    
    result = Mat::linspace(0.0, 10.0, -1);
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 0);
}

TEST(MatLinspaceRangeTest, RangeBasic) {
    // 基本的なrangeテスト
    Mat result = Mat::range(0.0, 2.0, 5.0); // 0, 2, 4
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    
    EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result(0, 2), 4.0);
}

TEST(MatLinspaceRangeTest, RangeNegativeStep) {
    // 負のステップ
    Mat result = Mat::range(10.0, -2.0, 0.0); // 10, 8, 6, 4, 2, 0
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 6);
    
    EXPECT_DOUBLE_EQ(result(0, 0), 10.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(result(0, 2), 6.0);
    EXPECT_DOUBLE_EQ(result(0, 3), 4.0);
    EXPECT_DOUBLE_EQ(result(0, 4), 2.0);
    EXPECT_DOUBLE_EQ(result(0, 5), 0.0);
}

TEST(MatLinspaceRangeTest, RangeZeroStep) {
    // ステップ0の場合
    Mat result = Mat::range(0.0, 0.0, 10.0);
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 0);
}