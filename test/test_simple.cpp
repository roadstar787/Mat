#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "test_common.h"

// 簡易テストを実行する関数
void run_simple_tests() {
    std::cout << "=== Matライブラリの簡易テスト ===" << std::endl;
    
    // 1. 基本的な行列の作成と表示
    std::cout << "\n1. 基本的な行列の作成と表示:" << std::endl;
    Mat m1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    m1.disp("行列m1");
    
    // 2. 統計関数のテスト
    std::cout << "\n2. 統計関数のテスト:" << std::endl;
    
    // 平均値
    Mat mean_result = m1.mean();
    std::cout << "全要素の平均値: " << mean_result(0, 0) << std::endl;
    
    Mat mean_col = m1.mean(0); // 列方向の平均
    std::cout << "各列の平均値: ";
    for (int i = 0; i < mean_col.cols(); ++i) {
        std::cout << mean_col(0, i) << " ";
    }
    std::cout << std::endl;
    
    Mat mean_row = m1.mean(1); // 行方向の平均
    std::cout << "各行の平均値: ";
    for (int i = 0; i < mean_row.rows(); ++i) {
        std::cout << mean_row(i, 0) << " ";
    }
    std::cout << std::endl;
    
    // 中央値
    Mat median_result = m1.median();
    std::cout << "全要素の中央値: " << median_result(0, 0) << std::endl;
    
    // 積
    Mat prod_result = m1.prod();
    std::cout << "全要素の積: " << prod_result(0, 0) << std::endl;
    
    // 累積和
    Mat cumsum_result = m1.cumsum();
    std::cout << "全要素の累積和:" << std::endl;
    cumsum_result.disp();
    
    // 3. 論理インデックス関数のテスト
    std::cout << "\n3. 論理インデックス関数のテスト:" << std::endl;
    Mat condition = {{1.0, 0.0, 3.0}, {0.0, 5.0, 0.0}};
    std::cout << "条件行列:" << std::endl;
    condition.disp();
    
    Mat indices = Mat::find(condition);
    std::cout << "非ゼロ要素の線形インデックス:" << std::endl;
    indices.disp();
    
    auto [rows, cols] = Mat::find2d(condition);
    std::cout << "非ゼロ要素の行・列インデックス:" << std::endl;
    std::cout << "行: "; rows.disp();
    std::cout << "列: "; cols.disp();
    
    // 4. 基本的なベクトル/行列関数のテスト
    std::cout << "\n4. 基本的なベクトル/行列関数のテスト:" << std::endl;
    
    // 行列の跡
    double trace_val = m1.trace();
    std::cout << "行列の跡: " << trace_val << std::endl;
    
    // ノルム
    Mat vec = {{3.0, 4.0}};
    double norm_val = vec.norm(2);
    std::cout << "ベクトルの2-ノルム: " << norm_val << std::endl;
    
    // 形状変更
    Mat reshaped = m1.reshape(3, 2);
    std::cout << "形状変更後(3x2):" << std::endl;
    reshaped.disp();
    
    // 反転
    Mat flipped = m1.flipud();
    std::cout << "上下反転後:" << std::endl;
    flipped.disp();
    
    Mat flipped_lr = m1.fliplr();
    std::cout << "左右反転後:" << std::endl;
    flipped_lr.disp();
    
    // 回転
    Mat rotated = m1.rot90(1);
    std::cout << "90度回転後:" << std::endl;
    rotated.disp();
    
    // 5. 対角関数のテスト
    std::cout << "\n5. 対角関数のテスト:" << std::endl;
    Mat diagonal = m1.diag();
    std::cout << "対角要素:" << std::endl;
    diagonal.disp();
    
    Mat diag_matrix = Mat::diag(diagonal);
    std::cout << "対角行列:" << std::endl;
    diag_matrix.disp();
    
    // 6. 三角行列のテスト
    std::cout << "\n6. 三角行列のテスト:" << std::endl;
    Mat triu_mat = m1.triu();
    std::cout << "上三角行列:" << std::endl;
    triu_mat.disp();
    
    Mat tril_mat = m1.tril();
    std::cout << "下三角行列:" << std::endl;
    tril_mat.disp();
    
    std::cout << "\n=== テスト完了 ===" << std::endl;
}

int main() {
    try {
        run_simple_tests();
        std::cout << "\nすべてのテストが正常に完了しました！" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "エラーが発生しました: " << e.what() << std::endl;
        return 1;
    }
}