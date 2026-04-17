#include "mat.h"

// Utility functions implementation

// 内積を計算する
Mat Mat::dot(const Mat& b) const {
    if ((rows() == 1 || cols() == 1) && (b.rows() == 1 || b.cols() == 1)) {
        if (numel() == b.numel()) {
            Eigen::Map<const Eigen::VectorXd> vec1(data.data(), data.size());
            Eigen::Map<const Eigen::VectorXd> vec2(b.data.data(), b.data.size());
            return Mat({{vec1.dot(vec2)}});
        }
    }
    return Mat({{0.0}});
}

// 外積を計算する（3次元ベクトルのみ）
Mat Mat::cross(const Mat& b) const {
    if ((rows() == 3 && cols() == 1) || (rows() == 1 && cols() == 3)) {
        if ((b.rows() == 3 && b.cols() == 1) || (b.rows() == 1 && b.cols() == 3)) {
            Eigen::Vector3d a_vec, b_vec;
            if (rows() == 3) { a_vec << data(0,0), data(1,0), data(2,0); }
            else { a_vec << data(0,0), data(0,1), data(0,2); }
            if (b.rows() == 3) { b_vec << b.data(0,0), b.data(1,0), b.data(2,0); }
            else { b_vec << b.data(0,0), b.data(0,1), b.data(0,2); }
            Eigen::Vector3d result_vec = a_vec.cross(b_vec);
            Mat result(3,1);
            result.data << result_vec(0), result_vec(1), result_vec(2);
            return result;
        }
    }
    return Mat::zeros(3,1);
}

// 要素ごとのatan2を計算する
Mat Mat::atan2(const Mat& Y, const Mat& X) {
    Mat res;
    res.data = Y.data.binaryExpr(X.data, [](double y, double x) { return std::atan2(y, x); });
    return res;
}

// 水平方向に連結する
Mat Mat::horizontalConcat(const Mat& b) const {
    Eigen::MatrixXd result(data.rows(), data.cols() + b.data.cols());
    result << data, b.data;
    return Mat(result);
}

// 垂直方向に連結する
Mat Mat::verticalConcat(const Mat& b) const {
    Eigen::MatrixXd result(data.rows() + b.data.rows(), data.cols());
    result << data, b.data;
    return Mat(result);
}

// 行列の一部を切り出す
Mat Mat::slice(int rowStart, int colStart, int rows, int cols) const {
    return Mat(data.block(rowStart, colStart, rows, cols));
}

// 行列を表示する
void Mat::disp(const std::string& label) const {
    if (!label.empty()) std::cout << label << " =" << std::endl;
    std::cout << data << std::endl << std::endl;
}

// 等間隔のベクトルを生成する
Mat Mat::linspace(double start, double end, int n) {
    if (n <= 0) return Mat(1, 0);
    if (n == 1) return Mat({{start}});
    Mat result(1, n);
    double step = (end - start) / (n - 1);
    for (int i = 0; i < n; ++i) result(0, i) = start + i * step;
    return result;
}

// 指定された範囲とステップでベクトルを生成する
Mat Mat::range(double start, double step, double end) {
    if (step == 0.0) return Mat(1, 0);
    std::vector<double> values;
    if (step > 0) {
        for (double val = start; val <= end; val += step) values.push_back(val);
    } else {
        for (double val = start; val >= end; val += step) values.push_back(val);
    }
    Mat result(1, static_cast<int>(values.size()));
    for (size_t i = 0; i < values.size(); ++i) result(0, static_cast<int>(i)) = values[i];
    return result;
}

// 条件を満たす要素の線形インデックスを返す
Mat Mat::find(const Mat& condition) {
    std::vector<int> indices;
    indices.reserve(condition.numel());
    for (int i = 0; i < condition.rows(); ++i) {
        for (int j = 0; j < condition.cols(); ++j) {
            if (condition(i, j) != 0.0) indices.push_back(i * condition.cols() + j);
        }
    }
    Mat result(static_cast<int>(indices.size()), 1);
    for (size_t k = 0; k < indices.size(); ++k) result(k, 0) = static_cast<double>(indices[k]);
    return result;
}

// 条件を満たす要素の行と列のインデックスを返す
std::pair<Mat, Mat> Mat::find2d(const Mat& condition) {
    std::vector<int> rowIndices, colIndices;
    rowIndices.reserve(condition.numel());
    colIndices.reserve(condition.numel());
    for (int i = 0; i < condition.rows(); ++i) {
        for (int j = 0; j < condition.cols(); ++j) {
            if (condition(i, j) != 0.0) {
                rowIndices.push_back(i + 1);
                colIndices.push_back(j + 1);
            }
        }
    }
    Mat rows(static_cast<int>(rowIndices.size()), 1);
    Mat cols(static_cast<int>(colIndices.size()), 1);
    for (size_t k = 0; k < rowIndices.size(); ++k) {
        rows(k, 0) = static_cast<double>(rowIndices[k]);
        cols(k, 0) = static_cast<double>(colIndices[k]);
    }
    return {rows, cols};
}

// 要素へのアクセス
// Element access operators
double& Mat::operator()(int r, int c) {
    return data(r, c);
}

// 要素へのアクセス（1次元インデックス）
double& Mat::operator()(int i) {
    return data(i);
}

// 要素へのアクセス（const版、1次元インデックス）
double Mat::operator()(int i) const {
    return data(i);
}

// スレッドインサート演算子（データに値を挿入）
// Stream insertion operator
template<typename T>
Mat& Mat::operator<<(const T& value) {
    data << value;
    return *this;
}

// 明示的インスタンセーション（一般的な型用）
// Explicit instantiation for common types if needed
template Mat& Mat::operator<<(const int& value);
template Mat& Mat::operator<<(const double& value);
template Mat& Mat::operator<<(const float& value);
