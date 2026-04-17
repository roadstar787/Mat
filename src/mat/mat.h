/**
 * @brief 行列演算をサポートするクラス（MATLAB風インターフェース）
 * 
 * このクラスはEigenライブラリを基盤とし、MATLABに似た行列操作を提供します。
 * コンストラクタ、演算子オーバーロード、静的メソッドを通じて、
 * 直感的な行列演算を実現します。
 */
#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <Eigen/Dense>
#include <limits>
#include <utility>

// 乱数生成のための前方宣言
class Mat;
Mat rand(int rows, int cols);
Mat rand(int rows, int cols, double min, double max);
Mat randn(int rows, int cols);
void setRandomSeed(unsigned int seed);
unsigned int getRandomSeed();

class Mat {
public:
    /**
     * @brief 行列データを格納するEigen::MatrixXd
     * 
     * このクラスの核心データ構造で、すべての行列演算の基となります。
     * Eigenライブラリの高性能な行列演算機能を利用します。
     */
    Eigen::MatrixXd data;

    // --- コンストラクタ ---

    /**
     * @brief デフォルトコンストラクタ
     * 
     * 0行0列の行列を初期化します。
     * Mat().rows() == 0, Mat().cols() == 0 となります。
     */
    Mat() = default;

    /**
     * @brief Eigen::MatrixXdからの変換コンストラクタ
     * @param m 元となるEigen::MatrixXd
     * 
     * 既存のEigen::MatrixXdからMatオブジェクトを作成します。
     * コピーされるため、元の行列は変更されません。
     */
    Mat(const Eigen::MatrixXd& m);

    /**
     * @brief 指定サイズのゼロ行列を初期化
     * @param r 行数
     * @param c 列数
     * 
     * 指定された行数と列数を持つゼロ行列（すべての要素が0）を作成します。
     * Mat(3, 4) は3行4列のゼロ行列を生成します。
     */
    Mat(int r, int c);
    
    /**
     * @brief 初期化リストからのコンストラクタ
     * @param list 二重の初期化リスト（{{1,2}, {3,4}}など）
     * 
     * C++11の初期化リスト構文を使って行列を定義します。
     * Mat m = {{1, 2, 3}, {4, 5, 6}} のように使用できます。
     * 行の長さが異なる場合は、最初の行に合わせて切り詰められます。
     */
    Mat(std::initializer_list<std::initializer_list<double>> list);

    // --- 基本プロパティ ---

    /**
     * @brief 行数を取得
     * @return 行数（int型）
     * 
     * 行列の行数を返します。例えば3x4行列の場合、3を返します。
     */
    int rows() const;

    /**
     * @brief 列数を取得
     * @return 列数（int型）
     * 
     * 行列の列数を返します。例えば3x4行列の場合、4を返します。
     */
    int cols() const;

    /**
     * @brief 要素の総数を取得
     * @return 要素の総数（行数×列数）
     * 
     * 行列に含まれる全要素の数を返します。
     * 例えば3x4行列の場合、12を返します。
     */
    int numel() const;

    // --- 要素アクセス (MATLAB風 0-based) ---

    /**
     * @brief 行列要素への参照（非const版）
     */
    double& operator()(int r, int c) { return data(r, c); }

    /**
     * @brief 行列要素の取得（const版）
     */
    double operator()(int r, int c) const;

    /**
     * @brief 線形インデックスでの要素アクセス
     */
    double& operator()(int i) { return data(i); }

    /**
     * @brief 線形インデックスでの要素アクセス（const版）
     */
    double operator()(int i) const;

    // --- 四則演算 (演算子オーバーロード) ---

    Mat operator+(const Mat& b) const;
    Mat operator-(const Mat& b) const;
    Mat operator*(double b) const;
    Mat operator/(double b) const;
    Mat mtimes(const Mat& b) const;
    Mat times(const Mat& b) const;

    // --- 代表的な関数 (Static) ---
    
    static Mat zeros(int r, int c) { return Mat(Eigen::MatrixXd::Zero(r, c)); }
    static Mat ones(int r, int c) { return Mat(Eigen::MatrixXd::Ones(r, c)); }

    static Mat diff(const Mat& A);
    static Mat movmean(const Mat& A, int k);
    static Mat atan2(const Mat& Y, const Mat& X);

    Mat transpose() const;
    Mat inverse() const;
    double determinant() const;

    static Mat eye(int n) { return Mat(Eigen::MatrixXd::Identity(n, n)); }
    static Mat eye(int r, int c) { return Mat(Eigen::MatrixXd::Identity(r, c)); }

    Mat horizontalConcat(const Mat& b) const;
    Mat verticalConcat(const Mat& b) const;

    Mat slice(int rowStart, int colStart, int rows, int cols) const;
    
    void disp(const std::string& label = "") const;

    static Mat linspace(double start, double end, int n);
    static Mat range(double start, double step, double end);

    Mat mean(int dim = -1) const;
    Mat std(int dim = -1) const;
    Mat sum(int dim = -1) const;
    Mat max(int dim = -1) const;
    Mat min(int dim = -1) const;
    Mat median(int dim = -1) const;
    Mat prod(int dim = -1) const;

    Mat cumsum(int dim = -1) const;
    Mat cumprod(int dim = -1) const;

    Mat dot(const Mat& b) const;
    Mat cross(const Mat& b) const;

    // === 追加のベクトル・行列関数 ===

    double trace() const;
    double norm(int p = 2) const;
    Mat reshape(int newRows, int newCols) const;
    Mat flipud() const;
    Mat fliplr() const;
    Mat rot90(int k = 1) const;
    Mat repmat(int m, int n) const;

    static Mat blkdiag(const std::vector<Mat>& matrices);

    Mat triu(int k = 0) const;
    Mat tril(int k = 0) const;
    Mat diag(int k = 0) const;
    static Mat diag(const Mat& v, int k = 0);

    // === 論理インデックス関数 ===

    static Mat find(const Mat& condition);
    
    static std::pair<Mat, Mat> find2d(const Mat& condition) {
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
};

#endif // MAT_H