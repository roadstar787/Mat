#include "mat.h"

// 四則演算の実装は Eigen の機能を利用してシンプルに実装します。

/**
 * @brief 行列の加算（要素ごとの加算）
 * @param b 加算する行列
 * @return 加算結果の新しい行列
 * 
 * 対応する要素ごとに加算を行います（MATLABの+演算子と同様）。
 */
Mat Mat::operator+(const Mat& b) const {
    return Mat(data.array() + b.data.array());
}

/**
 * @brief 行列の減算（要素ごとの減算）
 * @param b 減算する行列
 * @return 減算結果の新しい行列
 * 
 * 対応する要素ごとに減算を行います（MATLABの-演算子と同様）。
 */
Mat Mat::operator-(const Mat& b) const {
    return Mat(data.array() - b.data.array());
}

/**
 * @brief 行列とスカラーの乗算（要素ごとの乗算）
 * @param b 乗算するスカラー値
 * @return 乗算結果の新しい行列
 * 
 * 行列の各要素を指定されたスカラー値で乗算します。
 */
Mat Mat::operator*(double b) const {
    return Mat(data.array() * b);
}

/**
 * @brief 行列とスカラーの除算（要素ごとの除算）
 * @param b 除算するスカラー値
 * @return 除算結果の新しい行列
 * 
 * 行列の各要素を指定されたスカラー値で除算します。
 */
Mat Mat::operator/(double b) const {
    return Mat(data.array() / b);
}

/**
 * @brief 行列積（線形代数の内積）
 * @param b 乗算する行列
 * @return 行列積の結果
 * 
 * 線形代数における行列積（A * B）を計算します。
 * MATLABのA * Bに相当します。
 */
Mat Mat::mtimes(const Mat& b) const {
    return Mat(data * b.data);
}

/**
 * @brief 要素ごとの乗算（アダマール積）
 * @param b 乗算する行列
 * @return 要素ごとの乗算結果
 * 
 * 対応する要素ごとに乗算を行います（要素積）。
 * MATLABのA .* Bに相当します。
 */
Mat Mat::times(const Mat& b) const {
    return Mat(data.array() * b.data.array());
}
