#include <gtest/gtest.h>
#include "../src/mat/mat.h"

// 基本的なベクトル/行列関数のテスト
TEST(MatAdvancedFunctionsTest, TraceFunction) {
    Mat data = {{1.0, 2.0}, {3.0, 4.0}};
    double trace = data.trace();
    EXPECT_DOUBLE_EQ(trace, 5.0); // 1 + 4
    
    // 3x3行列の跡
    Mat data3 = {{1.0, 2.0, 3.0}, 
                 {4.0, 5.0, 6.0}, 
                 {7.0, 8.0, 9.0}};
    double trace3 = data3.trace();
    EXPECT_DOUBLE_EQ(trace3, 15.0); // 1 + 5 + 9
}

TEST(MatAdvancedFunctionsTest, NormFunction) {
    Mat data = {{3.0, 4.0}};
    double norm1 = data.norm(1); // 1-ノルム
    EXPECT_DOUBLE_EQ(norm1, 7.0); // |3| + |4| = 7
    
    double norm2 = data.norm(2); // 2-ノルム（ユークリッドノルム）
    EXPECT_DOUBLE_EQ(norm2, 5.0); // sqrt(3^2 + 4^2) = 5
    
    double normInf = data.norm(std::numeric_limits<int>::max()); // 無限大ノルム
    EXPECT_DOUBLE_EQ(normInf, 4.0); // max(|3|, |4|) = 4
}

TEST(MatAdvancedFunctionsTest, ReshapeFunction) {
    Mat data = {{1.0, 2.0, 3.0}, 
                {4.0, 5.0, 6.0}};
    
    Mat reshaped = data.reshape(3, 2);
    EXPECT_EQ(reshaped.rows(), 3);
    EXPECT_EQ(reshaped.cols(), 2);
    EXPECT_DOUBLE_EQ(reshaped(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(reshaped(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(reshaped(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(reshaped(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(reshaped(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(reshaped(2, 1), 6.0);
}

TEST(MatAdvancedFunctionsTest, FlipFunctions) {
    Mat data = {{1.0, 2.0, 3.0}, 
                {4.0, 5.0, 6.0}};
    
    // flipud: 上下反転
    Mat flippedud = data.flipud();
    EXPECT_DOUBLE_EQ(flippedud(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(flippedud(0, 1), 5.0);
    EXPECT_DOUBLE_EQ(flippedud(0, 2), 6.0);
    EXPECT_DOUBLE_EQ(flippedud(1, 0), 1.0);
    EXPECT_DOUBLE_EQ(flippedud(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(flippedud(1, 2), 3.0);
    
    // fliplr: 左右反転
    Mat fliplr = data.fliplr();
    EXPECT_DOUBLE_EQ(fliplr(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(fliplr(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(fliplr(0, 2), 1.0);
    EXPECT_DOUBLE_EQ(fliplr(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(fliplr(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(fliplr(1, 2), 4.0);
}

TEST(MatAdvancedFunctionsTest, Rot90Function) {
    Mat data = {{1.0, 2.0}, 
                {3.0, 4.0}};
    
    // 90度回転（時計回り）
    Mat rot90_1 = data.rot90(1);
    EXPECT_DOUBLE_EQ(rot90_1(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(rot90_1(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(rot90_1(1, 0), 1.0);
    EXPECT_DOUBLE_EQ(rot90_1(1, 1), 3.0);
    
    // 180度回転
    Mat rot90_2 = data.rot90(2);
    EXPECT_DOUBLE_EQ(rot90_2(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(rot90_2(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(rot90_2(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(rot90_2(1, 1), 1.0);
}

TEST(MatAdvancedFunctionsTest, RepmatFunction) {
    Mat data = {{1.0, 2.0}};
    
    // 2x3で繰り返し
    Mat repeated = data.repmat(2, 3);
    EXPECT_EQ(repeated.rows(), 2);
    EXPECT_EQ(repeated.cols(), 6);
    
    // 最初の行
    EXPECT_DOUBLE_EQ(repeated(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(repeated(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(repeated(0, 2), 1.0);
    EXPECT_DOUBLE_EQ(repeated(0, 3), 2.0);
    EXPECT_DOUBLE_EQ(repeated(0, 4), 1.0);
    EXPECT_DOUBLE_EQ(repeated(0, 5), 2.0);
    
    // 2行目
    EXPECT_DOUBLE_EQ(repeated(1, 0), 1.0);
    EXPECT_DOUBLE_EQ(repeated(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(repeated(1, 2), 1.0);
    EXPECT_DOUBLE_EQ(repeated(1, 3), 2.0);
    EXPECT_DOUBLE_EQ(repeated(1, 4), 1.0);
    EXPECT_DOUBLE_EQ(repeated(1, 5), 2.0);
}

TEST(MatAdvancedFunctionsTest, BlkdiagFunction) {
    Mat mat1 = {{1.0, 2.0}};
    Mat mat2 = {{3.0}, {4.0}};
    Mat mat3 = {{5.0}};
    
    // ブロック対角行列を生成
    Mat blockDiag = Mat::blkdiag({mat1, mat2, mat3});
    
    EXPECT_EQ(blockDiag.rows(), 4); // 1 + 2 + 1
    EXPECT_EQ(blockDiag.cols(), 4); // 2 + 1 + 1
    
    // ブロック1
    EXPECT_DOUBLE_EQ(blockDiag(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(blockDiag(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(blockDiag(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(blockDiag(1, 1), 0.0);
    
    // ブロック2
    EXPECT_DOUBLE_EQ(blockDiag(0, 2), 0.0);
    EXPECT_DOUBLE_EQ(blockDiag(1, 2), 3.0);
    EXPECT_DOUBLE_EQ(blockDiag(2, 2), 4.0);
    EXPECT_DOUBLE_EQ(blockDiag(3, 2), 0.0);
    
    // ブロック3
    EXPECT_DOUBLE_EQ(blockDiag(3, 3), 5.0);
}

TEST(MatAdvancedFunctionsTest, TriuTrilFunctions) {
    Mat data = {{1.0, 2.0, 3.0}, 
                {4.0, 5.0, 6.0}, 
                {7.0, 8.0, 9.0}};
    
    // 上三角行列
    Mat triuMat = data.triu();
    EXPECT_DOUBLE_EQ(triuMat(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(triuMat(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(triuMat(0, 2), 3.0);
    EXPECT_DOUBLE_EQ(triuMat(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(triuMat(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(triuMat(1, 2), 6.0);
    EXPECT_DOUBLE_EQ(triuMat(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(triuMat(2, 1), 0.0);
    EXPECT_DOUBLE_EQ(triuMat(2, 2), 9.0);
    
    // 下三角行列
    Mat trilMat = data.tril();
    EXPECT_DOUBLE_EQ(trilMat(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(trilMat(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(trilMat(0, 2), 0.0);
    EXPECT_DOUBLE_EQ(trilMat(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(trilMat(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(trilMat(1, 2), 0.0);
    EXPECT_DOUBLE_EQ(trilMat(2, 0), 7.0);
    EXPECT_DOUBLE_EQ(trilMat(2, 1), 8.0);
    EXPECT_DOUBLE_EQ(trilMat(2, 2), 9.0);
}

TEST(MatAdvancedFunctionsTest, DiagFunctions) {
    Mat data = {{1.0, 2.0, 3.0}, 
                {4.0, 5.0, 6.0}, 
                {7.0, 8.0, 9.0}};
    
    // 対角要素を抽出
    Mat diagonal = data.diag();
    EXPECT_EQ(diagonal.rows(), 3);
    EXPECT_EQ(diagonal.cols(), 1);
    EXPECT_DOUBLE_EQ(diagonal(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(diagonal(1, 0), 5.0);
    EXPECT_DOUBLE_EQ(diagonal(2, 0), 9.0);
    
    // 対角行列を生成
    Mat vec = {{1.0}, {2.0}, {3.0}};
    Mat diagMat = Mat::diag(vec);
    EXPECT_EQ(diagMat.rows(), 3);
    EXPECT_EQ(diagMat.cols(), 3);
    EXPECT_DOUBLE_EQ(diagMat(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(diagMat(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(diagMat(2, 2), 3.0);
    EXPECT_DOUBLE_EQ(diagMat(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(diagMat(1, 0), 0.0);
}

// 論理インデックス関数のテスト
TEST(MatLogicalIndexingTest, FindFunction) {
    Mat condition = {{1.0, 0.0, 3.0}, 
                     {0.0, 5.0, 0.0}};
    
    // 論理インデックスで要素を検索
    Mat indices = Mat::find(condition);
    
    // 期待されるインデックス（線形インデックス）
    // 位置(0,0): 0, (0,2): 2, (1,1): 4
    EXPECT_EQ(indices.rows(), 3);
    EXPECT_EQ(indices.cols(), 1);
    EXPECT_DOUBLE_EQ(indices(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(indices(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(indices(2, 0), 4.0);
}

TEST(MatLogicalIndexingTest, Find2dFunction) {
    Mat condition = {{0.0, 2.0, 0.0}, 
                     {3.0, 0.0, 4.0}};
    
    // 2次元インデックスで要素を検索
    auto [rows, cols] = Mat::find2d(condition);
    
    // 期待される行・列インデックス（1ベース）
    // 非ゼロ要素: (0,1), (1,0), (1,2)
    EXPECT_EQ(rows.rows(), 3);
    EXPECT_EQ(cols.rows(), 3);
    
    // 行インデックス
    EXPECT_DOUBLE_EQ(rows(0, 0), 1.0); // 0行目 -> 1
    EXPECT_DOUBLE_EQ(rows(1, 0), 2.0); // 1行目 -> 2
    EXPECT_DOUBLE_EQ(rows(2, 0), 2.0); // 1行目 -> 2
    
    // 列インデックス
    EXPECT_DOUBLE_EQ(cols(0, 0), 2.0); // 1列目 -> 2
    EXPECT_DOUBLE_EQ(cols(1, 0), 1.0); // 0列目 -> 1
    EXPECT_DOUBLE_EQ(cols(2, 0), 3.0); // 2列目 -> 3
}