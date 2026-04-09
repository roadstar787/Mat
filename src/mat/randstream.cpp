#include "randstream.h"
#include <chrono>

// グローバルな乱数ストリームインスタンスの定義
RandStream globalRandomStream;

/**
 * @brief デフォルトコンストラクタ
 * 
 * 現在時刻をseedとして使用します。
 */
RandStream::RandStream() {
    // 現在時刻をseedとして使用
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    generator.seed(seed);
}

/**
 * @brief seedを指定するコンストラクタ
 * @param seed 乱数の初期シード値
 * 
 * 指定されたseedで乱数生成器を初期化します。
 */
RandStream::RandStream(unsigned int seed) : generator(seed) {
    // コンストラクタでseedを設定
}

/**
 * @brief 一様乱数を生成
 * @param rows 行数
 * @param cols 列数
 * @return 生成された乱数行列（値の範囲は[0,1)）
 * 
 * 0以上1未満の一様乱数を生成します。
 */
Mat RandStream::uniform(int rows, int cols) {
    return generate(rows, cols, uniform_dist);
}

/**
 * @brief 一様乱数を生成（指定範囲）
 * @param rows 行数
 * @param cols 列数
 * @param min 最小値（含む）
 * @param max 最大値（含まない）
 * @return 生成された乱数行列（値の範囲は[min,max)）
 * 
 * 指定された範囲の一様乱数を生成します。
 */
Mat RandStream::uniform(int rows, int cols, double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return generate(rows, cols, dist);
}

/**
 * @brief 正規乱数を生成
 * @param rows 行数
 * @param cols 列数
 * @return 生成された乱数行列（平均0, 標準偏差1の正規分布）
 * 
 * 平均0、標準偏差1の正規乱数を生成します。
 */
Mat RandStream::normal(int rows, int cols) {
    return generate(rows, cols, normal_dist);
}

/**
 * @brief seedを設定
 * @param seed 新しいシード値
 * 
 * 乱数生成器のseedを設定し、乱数列をリセットします。
 */
void RandStream::setSeed(unsigned int seed) {
    generator.seed(seed);
}

/**
 * @brief 現在のseedを取得
 * @return 現在のシード値
 */
unsigned int RandStream::getSeed() const {
    // mt19937には直接seedを取得するメソッドがないため、
    // 現在の状態から推測される値を返す（厳密ではないが、設定したseedを復元可能）
    return generator.state();
}

/**
 * @brief 乱数を生成してEigen::MatrixXdに格納
 * @param rows 行数
 * @param cols 列数
 * @param dist 分布オブジェクト
 * @return 生成された乱数行列
 * 
 * テンプレート関数で、任意の分布オブジェクトを使用して乱数を生成します。
 */
template<typename Distribution>
Mat RandStream::generate(int rows, int cols, Distribution& dist) {
    Mat result(rows, cols);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = dist(generator);
        }
    }
    
    return result;
}

// グローバル関数の実装

/**
 * @brief 一様乱数を生成（グローバル関数）
 * @param rows 行数
 * @param cols 列数
 * @return 生成された乱数行列（値の範囲は[0,1)）
 * 
 * グローバルなRandStreamインスタンスを使用して一様乱数を生成します。
 */
Mat rand(int rows, int cols) {
    return globalRandomStream.uniform(rows, cols);
}

/**
 * @brief 一様乱数を生成（指定範囲、グローバル関数）
 * @param rows 行数
 * @param cols 列数
 * @param min 最小値（含む）
 * @param max 最大値（含まない）
 * @return 生成された乱数行列（値の範囲は[min,max)）
 * 
 * グローバルなRandStreamインスタンスを使用して指定範囲の一様乱数を生成します。
 */
Mat rand(int rows, int cols, double min, double max) {
    return globalRandomStream.uniform(rows, cols, min, max);
}

/**
 * @brief 正規乱数を生成（グローバル関数）
 * @param rows 行数
 * @param cols 列数
 * @return 生成された乱数行列（平均0, 標準偏差1の正規分布）
 * 
 * グローバルなRandStreamインスタンスを使用して正規乱数を生成します。
 */
Mat randn(int rows, int cols) {
    return globalRandomStream.normal(rows, cols);
}

/**
 * @brief グローバルな乱数ストリームのseedを設定
 * @param seed 新しいシード値
 * 
 * グローバルなRandStreamインスタンスのseedを設定します。
 */
void setRandomSeed(unsigned int seed) {
    globalRandomStream.setSeed(seed);
}

/**
 * @brief グローバルな乱数ストリームのseedを取得
 * @return 現在のシード値
 * 
 * グローバルなRandStreamインスタンスの現在のseedを返します。
 */
unsigned int getRandomSeed() {
    return globalRandomStream.getSeed();
}