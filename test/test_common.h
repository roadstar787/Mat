#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <gtest/gtest.h>
#include "../src/mat/mat.h"

// 共通ユーティリティ関数
template<typename T>
void ExpectMatricesEqual(const Mat& expected, const Mat& actual, double tolerance = 1e-10) {
    EXPECT_EQ(expected.rows(), actual.rows());
    EXPECT_EQ(expected.cols(), actual.cols());
    for (int i = 0; i < expected.rows(); ++i) {
        for (int j = 0; j < expected.cols(); ++j) {
            EXPECT_NEAR(expected(i, j), actual(i, j), tolerance);
        }
    }
}

// テストデータ作成ヘルパー
inline Mat CreateTestMatrix2x2() {
    return {{1.0, 2.0}, {3.0, 4.0}};
}

inline Mat CreateTestMatrix3x3() {
    return {{1.0, 2.0, 3.0}, 
            {4.0, 5.0, 6.0}, 
            {7.0, 8.0, 9.0}};
}

#endif // TEST_COMMON_H