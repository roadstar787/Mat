#include <gtest/gtest.h>
#include "../src/mat/mat.h"

TEST(MatVectorOpsTest, DotProduct) {
    // 内積のテスト
    Mat vec1 = {{1.0, 2.0, 3.0}};
    Mat vec2 = {{4.0, 5.0, 6.0}};
    Mat result = vec1.dot(vec2);
    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    EXPECT_DOUBLE_EQ(result(0, 0), 32.0);
    
    // 次元が合わない場合
    Mat vec3 = {{1.0, 2.0}};
    Mat result2 = vec1.dot(vec3);
    EXPECT_DOUBLE_EQ(result2(0, 0), 0.0); // 次元が合わないので0
    
    // 列ベクトルの場合
    Mat colVec1 = {{1.0}, {2.0}, {3.0}};
    Mat colVec2 = {{4.0}, {5.0}, {6.0}};
    Mat result3 = colVec1.dot(colVec2);
    EXPECT_DOUBLE_EQ(result3(0, 0), 32.0);
}

TEST(MatVectorOpsTest, CrossProduct) {
    // 外積のテスト
    Mat vec1 = {{1.0}, {0.0}, {0.0}}; // x軸方向
    Mat vec2 = {{0.0}, {1.0}, {0.0}}; // y軸方向
    Mat result = vec1.cross(vec2);
    // x × y = z なので {0, 0, 1}
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(2, 0), 1.0);
    
    // 逆順
    Mat result2 = vec2.cross(vec1);
    // y × x = -z なので {0, 0, -1}
    EXPECT_DOUBLE_EQ(result2(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result2(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result2(2, 0), -1.0);
    
    // 平行なベクトル（外積は0）
    Mat vec3 = {{2.0}, {0.0}, {0.0}};
    Mat result3 = vec1.cross(vec3);
    EXPECT_DOUBLE_EQ(result3(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result3(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result3(2, 0), 0.0);
    
    // 次元が合わない場合
    Mat vec4 = {{1.0, 2.0}}; // 2次元ベクトル
    Mat result4 = vec1.cross(vec4);
    EXPECT_EQ(result4.rows(), 3);
    EXPECT_EQ(result4.cols(), 1);
    EXPECT_DOUBLE_EQ(result4(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result4(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result4(2, 0), 0.0); // 条件を満たさないのでゼロベクトル
}

TEST(MatVectorOpsTest, Trace) {
    // トレースのテスト（対角要素の和）
    Mat mat = {{1.0, 2.0, 3.0},
               {4.0, 5.0, 6.0},
               {7.0, 8.0, 9.0}};
    // 現在の実装ではtraceメソッドがないため、このテストはスキップまたは実装後に追加
    // ここではプレースホルダーとしてコメントのみ
    // SUCCEED() << "Trace method not yet implemented";
}

TEST(MatVectorOpsTest, Norm) {
    // ノルムのテスト
    Mat vec = {{3.0, 4.0}}; // 2次元ベクトル
    // 現在の実装ではnormメソッドがないため、このテストはスキップまたは実装後に追加
    // SUCCEED() << "Norm method not yet implemented";
}

TEST(MatVectorOpsTest, Reshape) {
    // リシェイプのテスト
    Mat mat = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}}; // 1x6
    // 現在の実装ではreshapeメソッドがないため、このテストはスキップまたは実装後に追加
    // SUCCEED() << "Reshape method not yet implemented";
}