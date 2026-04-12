#include <gtest/gtest.h>
#include "../src/mat/mat.h"

// 統計関数の拡張テスト
TEST(MatStatisticalExtendedTest, MedianFunction) {
    // テストデータ: 1, 2, 3, 4, 5 -> median is 3
    Mat data = {{1.0}, {2.0}, {3.0}, {4.0}, {5.0}};
    Mat result = data.median();
    EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
    
    // テストデータ: 1, 2, 3, 4 -> median is (2+3)/2 = 2.5
    Mat data2 = {{1.0}, {2.0}, {3.0}, {4.0}};
    Mat result2 = data2.median();
    EXPECT_DOUBLE_EQ(result2(0, 0), 2.5);
    
    // 行方向の中央値
    Mat data3 = {{1.0, 2.0, 3.0}, 
                 {4.0, 5.0, 6.0}};
    Mat result3 = data3.median(0); // 各列の中央値
    EXPECT_DOUBLE_EQ(result3(0, 0), 2.5); // (1+4)/2
    EXPECT_DOUBLE_EQ(result3(0, 1), 3.5); // (2+5)/2
    EXPECT_DOUBLE_EQ(result3(0, 2), 4.5); // (3+6)/2
    
    // 列方向の中央値
    Mat result4 = data3.median(1); // 各行の中央値
    EXPECT_DOUBLE_EQ(result4(0, 0), 2.0); // (1+2+3)/3
    EXPECT_DOUBLE_EQ(result4(1, 0), 5.0); // (4+5+6)/3
}

TEST(MatStatisticalExtendedTest, ProdFunction) {
    // 全要素の積
    Mat data = {{2.0, 3.0}, {4.0, 5.0}};
    Mat result = data.prod();
    EXPECT_DOUBLE_EQ(result(0, 0), 120.0); // 2*3*4*5
    
    // 行方向の積（各列の積）
    Mat result2 = data.prod(0);
    EXPECT_DOUBLE_EQ(result2(0, 0), 8.0);  // 2*4
    EXPECT_DOUBLE_EQ(result2(0, 1), 15.0); // 3*5
    
    // 列方向の積（各行の積）
    Mat result3 = data.prod(1);
    EXPECT_DOUBLE_EQ(result3(0, 0), 6.0);  // 2*3
    EXPECT_DOUBLE_EQ(result3(1, 0), 20.0); // 4*5
}

TEST(MatStatisticalExtendedTest, CumsumFunction) {
    // 全要素の累積和
    Mat data = {{1.0, 2.0}, {3.0, 4.0}};
    Mat result = data.cumsum();
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 3.0);  // 1+2
    EXPECT_DOUBLE_EQ(result(1, 0), 4.0);  // 1+3
    EXPECT_DOUBLE_EQ(result(1, 1), 10.0); // 1+2+3+4
    
    // 行方向の累積和（各列の累積和）
    Mat result2 = data.cumsum(0);
    EXPECT_DOUBLE_EQ(result2(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result2(1, 0), 4.0);  // 1+3
    EXPECT_DOUBLE_EQ(result2(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result2(1, 1), 6.0);  // 2+4
    
    // 列方向の累積和（各行の累積和）
    Mat result3 = data.cumsum(1);
    EXPECT_DOUBLE_EQ(result3(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result3(0, 1), 3.0);  // 1+2
    EXPECT_DOUBLE_EQ(result3(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result3(1, 1), 7.0);  // 3+4
}

TEST(MatStatisticalExtendedTest, CumprodFunction) {
    // 全要素の累積積
    Mat data = {{1.0, 2.0}, {3.0, 4.0}};
    Mat result = data.cumprod();
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result(0, 1), 2.0);   // 1*2
    EXPECT_DOUBLE_EQ(result(1, 0), 3.0);   // 1*3
    EXPECT_DOUBLE_EQ(result(1, 1), 24.0);  // 1*2*3*4
    
    // 行方向の累積積（各列の累積積）
    Mat result2 = data.cumprod(0);
    EXPECT_DOUBLE_EQ(result2(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result2(1, 0), 3.0);   // 1*3
    EXPECT_DOUBLE_EQ(result2(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result2(1, 1), 8.0);   // 2*4
    
    // 列方向の累積積（各行の累積積）
    Mat result3 = data.cumprod(1);
    EXPECT_DOUBLE_EQ(result3(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result3(0, 1), 2.0);   // 1*2
    EXPECT_DOUBLE_EQ(result3(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(result3(1, 1), 12.0);  // 3*4
}