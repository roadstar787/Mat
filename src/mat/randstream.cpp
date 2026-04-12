/**
 * @brief 乱数生成ストリームの実装
 * 
 * このファイルでは、一様分布と正規分布の乱数生成を実装します。
 * C++11の乱数ライブラリを利用して、高品質な乱数を生成します。
 */

#include "randstream.h"
#include <random>
#include <chrono>
#include <algorithm>

namespace {
    // グローバルな乱数生成器
    std::mt19937 global_rng;
    
    // 乱数生成器の初期化フラグ
    bool rng_initialized = false;
    
    // 乱数生成器を初期化
    void initialize_rng() {
        if (!rng_initialized) {
            // 現在の時刻をシードとして使用
            global_rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            rng_initialized = true;
        }
    }
}

/**
 * @brief 一様分布乱数を生成
 * @param rows 行数
 * @param cols 列数
 * @param min 最小値（デフォルト: 0.0）
 * @param max 最大値（デフォルト: 1.0）
 * @return 乱数行列
 */
Mat rand(int rows, int cols, double min, double max) {
    initialize_rng();
    
    // 一様分布を作成
    std::uniform_real_distribution<double> dist(min, max);
    
    // 乱数行列を作成
    Mat result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = dist(global_rng);
        }
    }
    
    return result;
}

/**
 * @brief 一様分布乱数を生成（デフォルト範囲）
 * @param rows 行数
 * @param cols 列数
 * @return 乱数行列（範囲: [0, 1)）
 */
Mat rand(int rows, int cols) {
    return rand(rows, cols, 0.0, 1.0);
}

/**
 * @brief 正規分布乱数を生成
 * @param rows 行数
 * @param cols 列数
 * @param mean 平均値（デフォルト: 0.0）
 * @param std_dev 標準偏差（デフォルト: 1.0）
 * @return 乱数行列
 */
Mat randn(int rows, int cols, double mean, double std_dev) {
    initialize_rng();
    
    // 正規分布を作成
    std::normal_distribution<double> dist(mean, std_dev);
    
    // 乱数行列を作成
    Mat result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = dist(global_rng);
        }
    }
    
    return result;
}

/**
 * @brief 正規分布乱数を生成（デフォルトパラメータ）
 * @param rows 行数
 * @param cols 列数
 * @return 乱数行列（平均: 0, 標準偏差: 1）
 */
Mat randn(int rows, int cols) {
    return randn(rows, cols, 0.0, 1.0);
}

/**
 * @brief 乱数シードを設定
 * @param seed シード値
 */
void setRandomSeed(unsigned int seed) {
    global_rng.seed(seed);
    rng_initialized = true;
}

/**
 * @brief 現在の乱数シードを取得
 * @return 現在のシード値
 */
unsigned int getRandomSeed() {
    return global_rng();
}