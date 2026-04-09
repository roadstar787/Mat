#ifndef RANDSTREAM_H
#define RANDSTREAM_H

#include <random>
#include "mat.h"

/**
 * @brief 乱数ストリームを管理するクラス
 * 
 * このクラスは、クロスプラットフォームで再現性のある乱数生成を提供します。
 * Mersenne Twisterアルゴリズムを使用し、同じseedならすべてのプラットフォームで
 * 同じ乱数列を生成します。
 */
class RandStream {
public:
    /**
     * @brief デフォルトコンストラクタ
     * 
     * 現在時刻をseedとして使用します。
     */
    RandStream();
    
    /**
     * @brief seedを指定するコンストラクタ
     * @param seed 乱数の初期シード値
     * 
     * 指定されたseedで乱数生成器を初期化します。
     */
    RandStream(unsigned int seed);
    
    /**
     * @brief 一様乱数を生成
     * @param rows 行数
     * @param cols 列数
     * @return 生成された乱数行列（値の範囲は[0,1)）
     * 
     * 0以上1未満の一様乱数を生成します。
     */
    Mat uniform(int rows, int cols);
    
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
    Mat uniform(int rows, int cols, double min, double max);
    
    /**
     * @brief 正規乱数を生成
     * @param rows 行数
     * @param cols 列数
     * @return 生成された乱数行列（平均0, 標準偏差1の正規分布）
     * 
     * 平均0、標準偏差1の正規乱数を生成します。
     */
    Mat normal(int rows, int cols);
    
    /**
     * @brief seedを設定
     * @param seed 新しいシード値
     * 
     * 乱数生成器のseedを設定し、乱数列をリセットします。
     */
    void setSeed(unsigned int seed);
    
    /**
     * @brief 現在のseedを取得
     * @return 現在のシード値
     */
    unsigned int getSeed() const;

private:
    /**
     * @brief 乱数生成器（Mersenne Twister）
     * 
     * クロスプラットフォームで再現性のある乱数生成に使用されます。
     */
    std::mt19937 generator;
    
    /**
     * @brief 一様分布の分布オブジェクト
     * 
     * デフォルトでは[0,1)の範囲の一様分布を生成します。
     */
    std::uniform_real_distribution<double> uniform_dist;
    
    /**
     * @brief 正規分布の分布オブジェクト
     * 
     * 平均0、標準偏差1の正規分布を生成します。
     */
    std::normal_distribution<double> normal_dist;
    
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
    Mat generate(int rows, int cols, Distribution& dist);
};

/**
 * @brief グローバルな乱数ストリームインスタンス
 * 
 * 便利なグローバル関数は、このインスタンスを使用して乱数を生成します。
 */
extern RandStream globalRandomStream;

/**
 * @brief 一様乱数を生成（グローバル関数）
 * @param rows 行数
     * @param cols 列数
 * @return 生成された乱数行列（値の範囲は[0,1)）
 * 
 * グローバルなRandStreamインスタンスを使用して一様乱数を生成します。
 */
Mat rand(int rows, int cols);

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
Mat rand(int rows, int cols, double min, double max);

/**
 * @brief 正規乱数を生成（グローバル関数）
 * @param rows 行数
 * @param cols 列数
 * @return 生成された乱数行列（平均0, 標準偏差1の正規分布）
 * 
 * グローバルなRandStreamインスタンスを使用して正規乱数を生成します。
 */
Mat randn(int rows, int cols);

/**
 * @brief グローバルな乱数ストリームのseedを設定
 * @param seed 新しいシード値
 * 
 * グローバルなRandStreamインスタンスのseedを設定します。
 */
void setRandomSeed(unsigned int seed);

/**
 * @brief グローバルな乱数ストリームのseedを取得
 * @return 現在のシード値
 * 
 * グローバルなRandStreamインスタンスの現在のseedを返します。
 */
unsigned int getRandomSeed();

#endif // RANDSTREAM_H