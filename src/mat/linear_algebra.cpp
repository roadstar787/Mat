#include "mat.h"

// 線形代数系関数の実装を mat.h から分離

/**
 * @brief 転置行列を取得
 * @return 転置された行列
 * 
 * 行列の行と列を入れ替えた転置行列を返します。
 * MATLABの ' 演算子（例：A'）に相当します。
 */
Mat Mat::transpose() const {
    return Mat(data.transpose());
}

/**
 * @brief 逆行列を取得
 * @return 逆行列
 * 
 * 行列の逆行列を計算して返します。
 * MATLABの inv() 関数に相当します。
 * 正則行列（行列式が0でない行列）のみで動作します。
 */
Mat Mat::inverse() const {
    return Mat(data.inverse());
}

/**
 * @brief 行列式を計算
 * @return 行列式の値
 * 
 * 行列の行列式（デターミナント）を計算して返します。
 * MATLABの det() 関数に相当します。
 * 正方形行列のみで動作します。
 */
double Mat::determinant() const {
    return data.determinant();
}

/**
 * @brief 行列の形を変更
 * @param newRows 新しい行数
 * @param newCols 新しい列数
 * @return 形状が変更された行列
 * 
 * MATLABの reshape(A, m, n) に相当します。
 * 要素数が一致している必要があります。
 */
Mat Mat::reshape(int newRows, int newCols) const {
    if (newRows * newCols != numel()) {
        throw std::invalid_argument("Reshape dimensions must match total number of elements");
    }
    Eigen::MatrixXd reshaped = data.reshaped<Eigen::ColMajor>(newRows, newCols);
    return Mat(reshaped);
}

/**
 * @brief 行列を上下反転
 * @return 反転された行列
 * 
 * MATLABの flipud(A) に相当します。
 */
Mat Mat::flipud() const {
    Eigen::MatrixXd reversed = data.colwise().reverse();
    return Mat(reversed);
}

/**
 * @brief 行列を左右反転
 * @return 反転された行列
 * 
 * MATLABの fliplr(A) に相当します。
 */
Mat Mat::fliplr() const {
    Eigen::MatrixXd reversed = data.rowwise().reverse();
    return Mat(reversed);
}

/**
 * @brief 行列を90度回転
 * @param k 回転の回数（90度単位、正の値は時計回り）
 * @return 回転された行列
 * 
 * MATLABの rot90(A, k) に相当します。
 */
Mat Mat::rot90(int k) const {
    Mat result = *this;
    for (int i = 0; i < (k % 4); ++i) {
        result = result.transpose().flipud();
    }
    return result;
}

/**
 * @brief 行列を繰り返し生成
 * @param m 行方向の繰り返し回数
 * @param n 列方向の繰り返し回数
 * @return 繰り返し生成された行列
 * 
 * MATLABの repmat(A, m, n) に相当します。
 */
Mat Mat::repmat(int m, int n) const {
    if (m <= 0 || n <= 0) return Mat();
    Mat result(rows() * m, cols() * n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result.data.block(i * rows(), j * cols(), rows(), cols()) = data;
        }
    }
    return result;
}

/**
 * @brief ブロック対角行列を生成
 * @param matrices 対角に配置される行列のリスト
 * @return ブロック対角行列
 * 
 * MATLABの blkdiag(A, B, C, ...) に相当します。
 */
Mat Mat::blkdiag(const std::vector<Mat>& matrices) {
    if (matrices.empty()) return Mat();
    int totalRows = 0, totalCols = 0;
    for (const auto& mat : matrices) {
        totalRows += mat.rows();
        totalCols += mat.cols();
    }
    Mat result(totalRows, totalCols);
    int curR = 0, curC = 0;
    for (const auto& mat : matrices) {
        result.data.block(curR, curC, mat.rows(), mat.cols()) = mat.data;
        curR += mat.rows();
        curC += mat.cols();
    }
    return result;
}

/**
 * @brief 上三角行列を抽出
 * @param k 対角線からのオフセット（0が主対角線）
 * @return 上三角行列
 * 
 * MATLABの triu(A, k) に相当します。
 */
Mat Mat::triu(int k) const {
    Mat res = *this;
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            if (j < i + k) res(i, j) = 0.0;
        }
    }
    return res;
}

/**
 * @brief 下三角行列を抽出
 * @param k 対角線からのオフセット（0が主対角線）
 * @return 下三角行列
 * 
 * MATLABの tril(A, k) に相当します。
 */
Mat Mat::tril(int k) const {
    Mat res = *this;
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            if (j > i + k) res(i, j) = 0.0;
        }
    }
    return res;
}

/**
 * @brief 対角要素を抽出または生成
 * @param k 対角線からのオフセット（0が主対角線）
 * @return 対角要素からなるベクトル
 * 
 * MATLABの diag(A, k) に相当します。
 */
Mat Mat::diag(int k) const {
    std::vector<double> d;
    if (k >= 0) {
        int max = std::min(rows(), cols() - k);
        for (int i = 0; i < max; ++i) d.push_back(data(i, i + k));
    } else {
        int max = std::min(rows() + k, cols());
        for (int i = 0; i < max; ++i) d.push_back(data(i - k, i));
    }
    Mat result(static_cast<int>(d.size()), 1);
    for (size_t i = 0; i < d.size(); ++i) result(i, 0) = d[i];
    return result;
}

/**
 * @brief 対角行列を生成
 * @param v 対角要素となるベクトル
 * @param k 対角線からのオフセット（0が主対角線）
 * @return 対角行列
 * 
 * MATLABの diag(v, k) に相当します。
 */
Mat Mat::diag(const Mat& v, int k) {
    int size = v.rows() * v.cols();
    int matSize = size + std::abs(k);
    Mat result(matSize, matSize);
    int idx = 0;
    if (k >= 0) {
        for (int i = 0; i < size; ++i) result(i, i + k) = v(idx++);
    } else {
        for (int i = 0; i < size; ++i) result(i - k, i) = v(idx++);
    }
    return result;
}

/**
 * @brief 行列の跡（trace）を計算
 * @return 跡の値（対角要素の和）
 * 
 * MATLABの trace(A) に相当します。
 * 正方形行列のみで動作します。
 */
double Mat::trace() const {
    if (rows() != cols()) {
        throw std::invalid_argument("Trace can only be computed for square matrices");
    }
    return data.trace();
}

/**
 * @brief ベクトルノルムを計算
 * @param p ノルムの種類（1, 2, infinityなど）
 * @return ノルムの値
 * 
 * MATLABの norm(A, p) に相当します。
 */
double Mat::norm(int p) const {
    if (numel() == 0) return 0.0;
    switch (p) {
        case 1:
            return data.lpNorm<1>();
        case 2:
            return data.norm();
        case std::numeric_limits<int>::max():
            return data.lpNorm<Eigen::Infinity>();
        default:
            throw std::invalid_argument("Unsupported norm type");
    }
}
