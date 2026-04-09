###################################################
#
#
# Lastmodified:
#
###################################################

#include <gtest/gtest.h>
#include "mat.h"

// Matクラスのテスト
TEST(MatTest, ConstructorDefault) {
    Mat mat;
    EXPECT_EQ(mat.rows(), 0);
    EXPECT_EQ(mat.cols(), 0);
}

TEST(MatTest, ConstructorSize) {
    Mat mat(3, 4);
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 4);
}

TEST(MatTest, ConstructorInitializerList) {
    Mat mat = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    EXPECT_EQ(mat.rows(), 2);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_DOUBLE_EQ(mat(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(mat(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(mat(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(mat(1, 2), 6.0);
}

TEST(MatTest, StaticZeros) {
    Mat mat = Mat::zeros(2, 3);
    EXPECT_EQ(mat.rows(), 2);
    EXPECT_EQ(mat.cols(), 3);
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = 0; j < mat.cols(); ++j) {
            EXPECT_DOUBLE_EQ(mat(i, j), 0.0);
        }
    }
}

TEST(MatTest, StaticOnes) {
    Mat mat = Mat::ones(2, 3);
    EXPECT_EQ(mat.rows(), 2);
    EXPECT_EQ(mat.cols(), 3);
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = 0; j < mat.cols(); ++j) {
            EXPECT_DOUBLE_EQ(mat(i, j), 1.0);
        }
    }
}

TEST(MatTest, Addition) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = {{5.0, 6.0}, {7.0, 8.0}};
    Mat c = a + b;
    EXPECT_DOUBLE_EQ(c(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 12.0);
}

TEST(MatTest, Subtraction) {
    Mat a = {{5.0, 6.0}, {7.0, 8.0}};
    Mat b = {{1.0, 2.0}, {3.0, 4.0}};
    Mat c = a - b;
    EXPECT_DOUBLE_EQ(c(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 4.0);
}

TEST(MatTest, ScalarMultiplication) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = a * 2.0;
    EXPECT_DOUBLE_EQ(b(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(b(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(b(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(b(1, 1), 8.0);
}

TEST(MatTest, MatrixMultiplication) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = {{5.0, 6.0}, {7.0, 8.0}};
    Mat c = a.mtimes(b);
    EXPECT_DOUBLE_EQ(c(0, 0), 19.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 22.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 43.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 50.0);
}

TEST(MatTest, ElementWiseMultiplication) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = {{5.0, 6.0}, {7.0, 8.0}};
    Mat c = a.times(b);
    EXPECT_DOUBLE_EQ(c(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 12.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 21.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 32.0);
}

TEST(MatTest, Transpose) {
    Mat a = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    Mat b = a.transpose();
    EXPECT_EQ(b.rows(), 3);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(b(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(b(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(b(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(b(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(b(2, 1), 6.0);
}

TEST(MatTest, Inverse) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = a.inverse();
    Mat identity = a.mtimes(b);
    EXPECT_NEAR(identity(0, 0), 1.0, 1e-10);
    EXPECT_NEAR(identity(0, 1), 0.0, 1e-10);
    EXPECT_NEAR(identity(1, 0), 0.0, 1e-10);
    EXPECT_NEAR(identity(1, 1), 1.0, 1e-10);
}

TEST(MatTest, Determinant) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    EXPECT_NEAR(a.determinant(), -2.0, 1e-10);
    
    Mat b = {{2.0, 5.0, 3.0}, {1.0, 3.0, 2.0}, {4.0, 1.0, 1.0}};
    EXPECT_NEAR(b.determinant(), 10.0, 1e-10);
}

TEST(MatTest, EyeSquare) {
    Mat a = Mat::eye(3);
    EXPECT_EQ(a.rows(), 3);
    EXPECT_EQ(a.cols(), 3);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(a(2, 2), 1.0);
    EXPECT_DOUBLE_EQ(a(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(a(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(a(2, 0), 0.0);
}

TEST(MatTest, EyeRectangle) {
    Mat a = Mat::eye(2, 4);
    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 4);
    EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(a(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(a(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(a(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(a(0, 2), 0.0);
    EXPECT_DOUBLE_EQ(a(1, 3), 0.0);
}

TEST(MatTest, HorizontalConcat) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = {{5.0, 6.0}, {7.0, 8.0}};
    Mat c = a.horizontalConcat(b);
    EXPECT_EQ(c.rows(), 2);
    EXPECT_EQ(c.cols(), 4);
    EXPECT_DOUBLE_EQ(c(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(c(0, 2), 5.0);
    EXPECT_DOUBLE_EQ(c(0, 3), 6.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 4.0);
    EXPECT_DOUBLE_EQ(c(1, 2), 7.0);
    EXPECT_DOUBLE_EQ(c(1, 3), 8.0);
}

TEST(MatTest, VerticalConcat) {
    Mat a = {{1.0, 2.0}, {3.0, 4.0}};
    Mat b = {{5.0, 6.0}, {7.0, 8.0}};
    Mat c = a.verticalConcat(b);
    EXPECT_EQ(c.rows(), 4);
    EXPECT_EQ(c.cols(), 2);
    EXPECT_DOUBLE_EQ(c(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 4.0);
    EXPECT_DOUBLE_EQ(c(2, 0), 5.0);
    EXPECT_DOUBLE_EQ(c(2, 1), 6.0);
    EXPECT_DOUBLE_EQ(c(3, 0), 7.0);
    EXPECT_DOUBLE_EQ(c(3, 1), 8.0);
}

TEST(MatTest, Slice) {
    Mat a = {{1.0, 2.0, 3.0, 4.0}, 
             {5.0, 6.0, 7.0, 8.0}, 
             {9.0, 10.0, 11.0, 12.0}};
    Mat b = a.slice(0, 1, 2, 2);
    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_DOUBLE_EQ(b(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(b(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(b(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(b(1, 1), 7.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}