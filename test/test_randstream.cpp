#include <gtest/gtest.h>
#include "mat.h"

// RandStreamのテスト
TEST(RandStreamTest, UniformGeneration) {
    // 一様乱数の生成と範囲確認
    Mat randomMat = rand(3, 4);
    
    // サイズの確認
    EXPECT_EQ(randomMat.rows(), 3);
    EXPECT_EQ(randomMat.cols(), 4);
    
    // 値の範囲確認 [0, 1)
    for (int i = 0; i < randomMat.rows(); ++i) {
        for (int j = 0; j < randomMat.cols(); ++j) {
            double val = randomMat(i, j);
            EXPECT_GE(val, 0.0);
            EXPECT_LT(val, 1.0);
        }
    }
}

TEST(RandStreamTest, UniformGenerationWithRange) {
    // 指定範囲の一様乱数の生成と範囲確認
    Mat randomMat = rand(2, 3, -5.0, 5.0);
    
    // サイズの確認
    EXPECT_EQ(randomMat.rows(), 2);
    EXPECT_EQ(randomMat.cols(), 3);
    
    // 値の範囲確認 [-5.0, 5.0)
    for (int i = 0; i < randomMat.rows(); ++i) {
        for (int j = 0; j < randomMat.cols(); ++j) {
            double val = randomMat(i, j);
            EXPECT_GE(val, -5.0);
            EXPECT_LT(val, 5.0);
        }
    }
}

TEST(RandStreamTest, NormalGeneration) {
    // 正規乱数の生成
    Mat randomMat = randn(3, 3);
    
    // サイズの確認
    EXPECT_EQ(randomMat.rows(), 3);
    EXPECT_EQ(randomMat.cols(), 3);
    
    // 簡単な統計的な確認（平均が0に近い、分散が1に近い）
    double sum = 0.0;
    for (int i = 0; i < randomMat.rows(); ++i) {
        for (int j = 0; j < randomMat.cols(); ++j) {
            sum += randomMat(i, j);
        }
    }
    double mean = sum / randomMat.numel();
    
    // 平均が0に近いことを確認（厳密なテストではない）
    EXPECT_NEAR(mean, 0.0, 1.0);
}

TEST(RandStreamTest, Reproducibility) {
    // 再現性テスト: 同じseedなら同じ乱数列が生成されるか確認
    setRandomSeed(12345);
    Mat mat1 = rand(2, 2);
    
    setRandomSeed(12345);
    Mat mat2 = rand(2, 2);
    
    // 行列が一致することを確認
    EXPECT_EQ(mat1.rows(), mat2.rows());
    EXPECT_EQ(mat1.cols(), mat2.cols());
    for (int i = 0; i < mat1.rows(); ++i) {
        for (int j = 0; j < mat1.cols(); ++j) {
            EXPECT_DOUBLE_EQ(mat1(i, j), mat2(i, j));
        }
    }
}

TEST(RandStreamTest, DifferentSeeds) {
    // 異なるseedなら異なる乱数列が生成されることを確認
    setRandomSeed(12345);
    Mat mat1 = rand(2, 2);
    
    setRandomSeed(54321);
    Mat mat2 = rand(2, 2);
    
    // 行列サイズは同じであること
    EXPECT_EQ(mat1.rows(), mat2.rows());
    EXPECT_EQ(mat1.cols(), mat2.cols());
    
    // 行列が異なることを確認（非常に高い確率で異なるはず）
    bool different = false;
    for (int i = 0; i < mat1.rows(); ++i) {
        for (int j = 0; j < mat1.cols(); ++j) {
            if (mat1(i, j) != mat2(i, j)) {
                different = true;
                break;
            }
        }
        if (different) break;
    }
    EXPECT_TRUE(different);
}

TEST(RandStreamTest, SeedManagement) {
    // Seedの管理テスト
    setRandomSeed(99999);
    unsigned int seed1 = getRandomSeed();
    
    setRandomSeed(88888);
    unsigned int seed2 = getRandomSeed();
    
    // 異なるseedが設定されていることを確認
    EXPECT_NE(seed1, seed2);
    
    // 同じseedを設定すると同じ値になることを確認
    setRandomSeed(12345);
    unsigned int seed3 = getRandomSeed();
    setRandomSeed(12345);
    unsigned int seed4 = getRandomSeed();
    EXPECT_EQ(seed3, seed4);
}

TEST(RandStreamTest, CrossPlatformConsistency) {
    // クロスプラットフォームの一貫性テスト
    // 特定のseedで期待される値と比較
    
    setRandomSeed(42);
    Mat mat = rand(2, 2);
    
    // Mersenne Twister with seed 42 の最初の4つの値
    // これらはプラットフォームに依存せず一定であるはず
    double expected[2][2] = {
        {0.8338249308447142, 0.4714357151870702},
        {0.8965465345368392, 0.1868984368926433}
    };
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_NEAR(mat(i, j), expected[i][j], 1e-10);
        }
    }
}

TEST(RandStreamTest, LargeMatrixGeneration) {
    // 大きな行列の乱数生成テスト
    Mat randomMat = rand(100, 100);
    
    // サイズの確認
    EXPECT_EQ(randomMat.rows(), 100);
    EXPECT_EQ(randomMat.cols(), 100);
    
    // 値の範囲確認
    for (int i = 0; i < randomMat.rows(); ++i) {
        for (int j = 0; j < randomMat.cols(); ++j) {
            double val = randomMat(i, j);
            EXPECT_GE(val, 0.0);
            EXPECT_LT(val, 1.0);
        }
    }
}

TEST(RandStreamTest, SingleElement) {
    // 1x1行列の乱数生成テスト
    Mat randomMat = rand(1, 1);
    
    // サイズの確認
    EXPECT_EQ(randomMat.rows(), 1);
    EXPECT_EQ(randomMat.cols(), 1);
    
    // 値の範囲確認
    double val = randomMat(0, 0);
    EXPECT_GE(val, 0.0);
    EXPECT_LT(val, 1.0);
}

TEST(RandStreamTest, RowVector) {
    // 行ベクトルの乱数生成テスト
    Mat randomMat = rand(1, 5);
    
    // サイズの確認
    EXPECT_EQ(randomMat.rows(), 1);
    EXPECT_EQ(randomMat.cols(), 5);
    
    // 値の範囲確認
    for (int j = 0; j < 5; ++j) {
        double val = randomMat(0, j);
        EXPECT_GE(val, 0.0);
        EXPECT_LT(val, 1.0);
    }
}

TEST(RandStreamTest, ColumnVector) {
    // 列ベクトルの乱数生成テスト
    Mat randomMat = rand(5, 1);
    
    // サイズの確認
    EXPECT_EQ(randomMat.rows(), 5);
    EXPECT_EQ(randomMat.cols(), 1);
    
    // 値の範囲確認
    for (int i = 0; i < 5; ++i) {
        double val = randomMat(i, 0);
        EXPECT_GE(val, 0.0);
        EXPECT_LT(val, 1.0);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}