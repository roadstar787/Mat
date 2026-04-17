#include "mat.h"

// 統計系関数の実装を mat.h から分離

// 各次元における平均を計算する
Mat Mat::mean(int dim) const {
    if (dim == -1) {
        return Mat({{data.mean()}});
    } else if (dim == 0) {
        Eigen::MatrixXd result = data.colwise().mean();
        return Mat(result);
    } else if (dim == 1) {
        Eigen::MatrixXd result = data.rowwise().mean();
        return Mat(result);
    } else {
        return Mat({{data.mean()}});
    }
}

// 各次元における標準偏差を計算する
Mat Mat::std(int dim) const {
    if (dim == -1) {
        double mean_val = data.mean();
        double variance = (data.array() - mean_val).square().sum() / data.size();
        return Mat({{std::sqrt(variance)}});
    } else if (dim == 0) {
        Eigen::MatrixXd result(data.cols(), 1);
        for (int j = 0; j < data.cols(); ++j) {
            double col_mean = data.col(j).mean();
            double variance = (data.col(j).array() - col_mean).square().sum() / data.rows();
            result(j, 0) = std::sqrt(variance);
        }
        return Mat(result.transpose());
    } else if (dim == 1) {
        Eigen::MatrixXd result(data.rows(), 1);
        for (int i = 0; i < data.rows(); ++i) {
            double row_mean = data.row(i).mean();
            double variance = (data.row(i).array() - row_mean).square().sum() / data.cols();
            result(i, 0) = std::sqrt(variance);
        }
        return Mat(result);
    } else {
        double mean_val = data.mean();
        double variance = (data.array() - mean_val).square().sum() / data.size();
        return Mat({{std::sqrt(variance)}});
    }
}

// 各次元における合計を計算する
Mat Mat::sum(int dim) const {
    if (dim == -1) {
        return Mat({{data.sum()}});
    } else if (dim == 0) {
        Eigen::MatrixXd result = data.colwise().sum();
        return Mat(result);
    } else if (dim == 1) {
        Eigen::MatrixXd result = data.rowwise().sum();
        return Mat(result);
    } else {
        return Mat({{data.sum()}});
    }
}

// 各次元における最大値を計算する
Mat Mat::max(int dim) const {
    if (dim == -1) {
        return Mat({{data.maxCoeff()}});
    } else if (dim == 0) {
        Eigen::MatrixXd result(data.cols(), 1);
        for (int j = 0; j < data.cols(); ++j) result(j, 0) = data.col(j).maxCoeff();
        return Mat(result.transpose());
    } else if (dim == 1) {
        Eigen::MatrixXd result(data.rows(), 1);
        for (int i = 0; i < data.rows(); ++i) result(i, 0) = data.row(i).maxCoeff();
        return Mat(result);
    } else {
        return Mat({{data.maxCoeff()}});
    }
}

// 各次元における最小値を計算する
Mat Mat::min(int dim) const {
    if (dim == -1) {
        return Mat({{data.minCoeff()}});
    } else if (dim == 0) {
        Eigen::MatrixXd result(data.cols(), 1);
        for (int j = 0; j < data.cols(); ++j) result(j, 0) = data.col(j).minCoeff();
        return Mat(result.transpose());
    } else if (dim == 1) {
        Eigen::MatrixXd result(data.rows(), 1);
        for (int i = 0; i < data.rows(); ++i) result(i, 0) = data.row(i).minCoeff();
        return Mat(result);
    } else {
        return Mat({{data.minCoeff()}});
    }
}

// 各次元における中央値を計算する
Mat Mat::median(int dim) const {
    if (dim == -1) {
        Eigen::VectorXd flat = data;
        std::sort(flat.data(), flat.data() + flat.size());
        size_t n = flat.size();
        if (n == 0) return Mat({{0.0}});
        if (n % 2 == 0) return Mat({{(flat(n/2 - 1) + flat(n/2)) / 2.0}});
        return Mat({{flat(n/2)}});
    } else if (dim == 0) {
        Mat result(1, cols());
        for (int j = 0; j < cols(); ++j) {
            Eigen::VectorXd col = data.col(j);
            std::sort(col.data(), col.data() + col.size());
            size_t n = col.size();
            if (n == 0) result(0, j) = 0.0;
            else if (n % 2 == 0) result(0, j) = (col(n/2 - 1) + col(n/2)) / 2.0;
            else result(0, j) = col(n/2);
        }
        return result;
    } else if (dim == 1) {
        Mat result(rows(), 1);
        for (int i = 0; i < rows(); ++i) {
            Eigen::VectorXd row = data.row(i);
            std::sort(row.data(), row.data() + row.size());
            size_t n = row.size();
            if (n == 0) result(i, 0) = 0.0;
            else if (n % 2 == 0) result(i, 0) = (row(n/2 - 1) + row(n/2)) / 2.0;
            else result(i, 0) = row(n/2);
        }
        return result;
    } else {
        return median();
    }
}

// 各次元における積を計算する
Mat Mat::prod(int dim) const {
    if (dim == -1) {
        return Mat({{data.prod()}});
    } else if (dim == 0) {
        Eigen::MatrixXd result(data.cols(), 1);
        for (int j = 0; j < data.cols(); ++j) result(j, 0) = data.col(j).prod();
        return Mat(result.transpose());
    } else if (dim == 1) {
        Eigen::MatrixXd result(data.rows(), 1);
        for (int i = 0; i < data.rows(); ++i) result(i, 0) = data.row(i).prod();
        return Mat(result);
    } else {
        return Mat({{data.prod()}});
    }
}

// 各次元における累積和を計算する
Mat Mat::cumsum(int dim) const {
    if (dim == -1) {
        Eigen::VectorXd flat = data;
        Eigen::VectorXd cumsum(flat.size());
        double sum = 0.0;
        for (int i = 0; i < flat.size(); ++i) { sum += flat(i); cumsum(i) = sum; }
        return Mat(cumsum);
    } else if (dim == 0) {
        Eigen::MatrixXd result = data;
        for (int j = 0; j < data.cols(); ++j)
            for (int i = 1; i < data.rows(); ++i) result(i, j) += result(i-1, j);
        return Mat(result);
    } else if (dim == 1) {
        Eigen::MatrixXd result = data;
        for (int i = 0; i < data.rows(); ++i)
            for (int j = 1; j < data.cols(); ++j) result(i, j) += result(i, j-1);
        return Mat(result);
    } else {
        return cumsum();
    }
}

// 各次元における累積積を計算する
Mat Mat::cumprod(int dim) const {
    if (dim == -1) {
        Eigen::VectorXd flat = data;
        Eigen::VectorXd cumprod(flat.size());
        double prod = 1.0;
        for (int i = 0; i < flat.size(); ++i) { prod *= flat(i); cumprod(i) = prod; }
        return Mat(cumprod);
    } else if (dim == 0) {
        Eigen::MatrixXd result = data;
        for (int j = 0; j < data.cols(); ++j)
            for (int i = 1; i < data.rows(); ++i) result(i, j) *= result(i-1, j);
        return Mat(result);
    } else if (dim == 1) {
        Eigen::MatrixXd result = data;
        for (int i = 0; i < data.rows(); ++i)
            for (int j = 1; j < data.cols(); ++j) result(i, j) *= result(i, j-1);
        return Mat(result);
    } else {
        return cumprod();
    }
}

// 要素間の差分を計算する
Mat Mat::diff(const Mat& A) {
    if (A.numel() <= 1) return Mat();
    if (A.rows() == 1)
        return Mat(A.data.rightCols(A.cols() - 1) - A.data.leftCols(A.cols() - 1));
    else
        return Mat(A.data.bottomRows(A.rows() - 1) - A.data.topRows(A.rows() - 1));
}

// 指定された窓サイズで移動平均を計算する
Mat Mat::movmean(const Mat& A, int k) {
    Mat res = A;
    int n = A.numel();
    int r = A.rows();
    int c = A.cols();
    bool isRow = (r == 1);
    for (int i = 0; i < n; ++i) {
        int start = std::max(0, i - k / 2);
        int end = std::min(n - 1, i + (k - 1) / 2);
        int len = end - start + 1;
        if (isRow) res.data(0, i) = A.data.block(0, start, 1, len).mean();
        else res.data(i % r, i / r) = A.data.block(start % r, start / r, (isRow?1:len), (isRow?len:1)).mean();
    }
    return res;
}
