// mat.cppの実装ファイル
// 現在はmat.hにすべての実装が含まれているため、空の実装ファイル
#include "mat.h"

// --- コンストラクタ ---

/**
 * @brief Eigen::MatrixXdからの変換コンストラクタ
 * @param m 元となるEigen::MatrixXd
 * 
 * 既存のEigen::MatrixXdからMatオブジェクトを作成します。
 * コピーされるため、元の行列は変更されません。
 */
Mat::Mat(const Eigen::MatrixXd& m) : data(m) {}

/**
 * @brief 指定サイズのゼロ行列を初期化
 * @param r 行数
 * @param c 列数
 * 
 * 指定された行数と列数を持つゼロ行列（すべての要素が0）を作成します。
 * Mat(3, 4) は3行4列のゼロ行列を生成します。
 */
Mat::Mat(int r, int c) : data(Eigen::MatrixXd::Zero(r, c)) {}

/**
 * @brief 初期化リストからのコンストラクタ
 * @param list 二重の初期化リスト（{{1,2}, {3,4}}など）
 * 
 * C++11の初期化リスト構文を使って行列を定義します。
 * Mat m = {{1, 2, 3}, {4, 5, 6}} のように使用できます。
 * 行の長さが異なる場合は、最初の行に合わせて切り詰められます。
 */
Mat::Mat(std::initializer_list<std::initializer_list<double>> list) {
    int rows = list.size();
    int cols = (rows > 0) ? list.begin()->size() : 0;
    data.resize(rows, cols);
    int i = 0;
    for (auto& row : list) {
        int j = 0;
        for (auto& val : row) data(i, j++) = val;
        i++;
    }
}

// --- 基本プロパティ ---

/**
 * @brief 行数を取得
 * @return 行数（int型）
 * 
 * 行列の行数を返します。例えば3x4行列の場合、3を返します。
 */
int Mat::rows() const { return (int)data.rows(); }

/**
 * @brief 列数を取得
 * @return 列数（int型）
 * 
 * 行列の列数を返します。例えば3x4行列の場合、4を返します。
 */
int Mat::cols() const { return (int)data.cols(); }

/**
 * @brief 要素の総数を取得
 * @return 要素の総数（行数×列数）
 * 
 * 行列に含まれる全要素の数を返します。
 * 例えば3x4行列の場合、12を返します。
 */
int Mat::numel() const { return (int)data.size(); }

// --- 要素アクセス (MATLAB風 0-based) ---

/**
 * @brief 行列要素の取得（const版）
 * @param r 行インデックス（0から始まる）
 * @param c 列インデックス（0から始まる）
 * @return 指定位置の要素の値
 * 
 * constなMatオブジェクトから要素を取得する場合に使用します。
 * 値の変更はできません。
 */
double Mat::operator()(int r, int c) const { return data(r, c); }

/**
 * @brief 線形インデックスでの要素取得（const版）
 * @param i 線形インデックス（0から始まる）
 * @return 指定位置の要素の値
 * 
 * constなMatオブジェクトから線形インデックスで要素を取得する場合に使用します。
 * 値の変更はできません。
 */
double Mat::operator()(int i) const { return data(i); }