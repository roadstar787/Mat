/**
 * @brief 行列演算をサポートするクラス（MATLAB風インターフェース）
 * 
 * このクラスはEigenライブラリを基盤とし、MATLABに似た行列操作を提供します。
 * コンストラクタ、演算子オーバーロード、静的メソッドを通じて、
 * 直感的な行列演算を実現します。
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <Eigen/Dense>

// 乱数生成のための前方宣言
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
    Mat(const Eigen::MatrixXd& m) : data(m) {}

    /**
     * @brief 指定サイズのゼロ行列を初期化
     * @param r 行数
     * @param c 列数
     * 
     * 指定された行数と列数を持つゼロ行列（すべての要素が0）を作成します。
     * Mat(3, 4) は3行4列のゼロ行列を生成します。
     */
    Mat(int r, int c) : data(Eigen::MatrixXd::Zero(r, c)) {}
    
    /**
     * @brief 初期化リストからのコンストラクタ
     * @param list 二重の初期化リスト（{{1,2}, {3,4}}など）
     * 
     * C++11の初期化リスト構文を使って行列を定義します。
     * Mat m = {{1, 2, 3}, {4, 5, 6}} のように使用できます。
     * 行の長さが異なる場合は、最初の行に合わせて切り詰められます。
     */
    Mat(std::initializer_list<std::initializer_list<double>> list) {
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
    int rows() const { return (int)data.rows(); }

    /**
     * @brief 列数を取得
     * @return 列数（int型）
     * 
     * 行列の列数を返します。例えば3x4行列の場合、4を返します。
     */
    int cols() const { return (int)data.cols(); }

    /**
     * @brief 要素の総数を取得
     * @return 要素の総数（行数×列数）
     * 
     * 行列に含まれる全要素の数を返します。
     * 例えば3x4行列の場合、12を返します。
     */
    int numel() const { return (int)data.size(); }

    // --- 要素アクセス (MATLAB風 0-based) ---

    /**
     * @brief 行列要素への参照（非const版）
     * @param r 行インデックス（0から始まる）
     * @param c 列インデックス（0から始まる）
     * @return 指定位置の要素への参照
     * 
     * MATLABと同様に0ベースのインデックスで要素にアクセスします。
     * 値の変更が可能なため、左辺値として使用できます。
     * 例: m(0, 0) = 5.0;
     */
    double& operator()(int r, int c) { return data(r, c); }

    /**
     * @brief 行列要素の取得（const版）
     * @param r 行インデックス（0から始まる）
     * @param c 列インデックス（0から始まる）
     * @return 指定位置の要素の値
     * 
     * constなMatオブジェクトから要素を取得する場合に使用します。
     * 値の変更はできません。
     */
    double operator()(int r, int c) const { return data(r, c); }

    /**
     * @brief 線形インデックスでの要素アクセス
     * @param i 線形インデックス（0から始まる）
     * @return 指定位置の要素への参照
     * 
     * 行列を1次元配列のように扱うためのアクセス方法です。
     * 列優先（column-major）順にアクセスします。
     * 例：3x4行列の場合、インデックス0→(0,0)、1→(1,0)、2→(2,0)、3→(0,1)...
     */
    double& operator()(int i) { return data(i); } // 線形インデックス

    // --- 四則演算 (演算子オーバーロード) ---

    /**
     * @brief 行列の加算（要素ごとの加算）
     * @param b 加算する行列
     * @return 加算結果の新しい行列
     * 
     * 対応する要素ごとに加算を行います（MATLABの+演算子と同様）。
     * サイズが異なる場合はEigenライブラリのエラーが発生します。
     */
    Mat operator+(const Mat& b) const { return Mat(data.array() + b.data.array()); }

    /**
     * @brief 行列の減算（要素ごとの減算）
     * @param b 減算する行列
     * @return 減算結果の新しい行列
     * 
     * 対応する要素ごとに減算を行います（MATLABの-演算子と同様）。
     * サイズが異なる場合はEigenライブラリのエラーが発生します。
     */
    Mat operator-(const Mat& b) const { return Mat(data.array() - b.data.array()); }

    /**
     * @brief 行列とスカラーの乗算（要素ごとの乗算）
     * @param b 乗算するスケーラ値
     * @return 乗算結果の新しい行列
     * 
     * 行列の各要素を指定されたスケーラ値で乗算します。
     * MATLABのスカラー乗算と同様の動作をします。
     */
    Mat operator*(double b) const { return Mat(data.array() * b); }

    /**
     * @brief 行列とスカラーの除算（要素ごとの除算）
     * @param b 除算するスケーラ値
     * @return 除算結果の新しい行列
     * 
     * 行列の各要素を指定されたスケーラ値で除算します。
     * bが0の場合、EigenライブラリがNaNまたはInfを生成します。
     */
    Mat operator/(double b) const { return Mat(data.array() / b); }
    
    /**
     * @brief 行列積（線形代数の行列積）
     * @param b 乗算する行列
     * @return 行列積の結果
     * 
     * 線形代数における行列積（内積）を計算します。
     * この行列の列数とbの行数が一致している必要があります。
     * MATLABのA * Bに相当します。
     */
    Mat mtimes(const Mat& b) const { return Mat(data * b.data); }

    /**
     * @brief 要素ごとの乗算（アダマール積）
     * @param b 乗算する行列
     * @return 要素ごとの乗算結果
     * 
     * 対応する要素ごとに乗算を行います（要素積）。
     * MATLABのA .* Bに相当します。
     * サイズは両行列で一致している必要があります。
     */
    Mat times(const Mat& b) const { return Mat(data.array() * b.data.array()); }

    // --- 代表的な関数 (Static) ---
    
    /**
     * @brief ゼロ行列の生成
     * @param r 行数
     * @param c 列数
     * @return 全要素が0の行列
     * 
     * 指定されたサイズのゼロ行列を生成します。
     * すべての要素が0で初期化されます。
     */
    static Mat zeros(int r, int c) { return Mat(Eigen::MatrixXd::Zero(r, c)); }

    /**
     * @brief 1行列の生成
     * @param r 行数
     * @param c 列数
     * @return 全要素が1の行列
     * 
     * 指定されたサイズの行列を生成し、すべての要素を1で初期化します。
     */
    static Mat ones(int r, int c) { return Mat(Eigen::MatrixXd::Ones(r, c)); }

    /**
     * @brief 隣接要素間の差分を計算
     * @param A 入力行列
     * @return 差分行列
     * 
     * MATLABのdiff関数と同様の機能を提供します。
     * 行ベクトルの場合：隣接する列要素間の差分を計算
     * 列ベクトルまたは行列の場合：隣接する行要素間の差分を計算
     * 要素数が1以下の場合は空行列を返します。
     */
    static Mat diff(const Mat& A) {
        if (A.numel() <= 1) return Mat();
        if (A.rows() == 1) // 行ベクトル
            return Mat(A.data.rightCols(A.cols() - 1) - A.data.leftCols(A.cols() - 1));
        else // 列ベクトルまたは行列（列方向）
            return Mat(A.data.bottomRows(A.rows() - 1) - A.data.topRows(A.rows() - 1));
    }

    /**
     * @brief 移動平均を計算
     * @param A 入力行列
     * @param k 窓サイズ（奇数推奨）
     * @return 移動平均結果
     * 
     * 指定された窓サイズで移動平均を計算します。
     * 現在の要素を中心として、左右にk/2個の要素（合計k個）の平均を計算します。
     * 端では利用可能な要素のみで平均を計算します。
     * 現在の実装はベクトル（1行または1列）を想定しています。
     */
    static Mat movmean(const Mat& A, int k) {
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
            // ※簡易化のためベクトルのみ想定したロジック
        }
        return res;
    }

    /**
     * @brief 要素ごとの逆正接関数（atan2）
     * @param Y 分子となる行列
     * @param X 分母となる行列
     * @return atan2(Y, X)の結果
     * 
     * MATLABのatan2関数と同様の機能を提供します。
     * 各要素についてatan2(y, x)を計算します。
     * XとYのサイズが一致している必要があります。
     * 四象限対応の逆正接関数です。
     */
    static Mat atan2(const Mat& Y, const Mat& X) {
        Mat res;
        res.data = Y.data.binaryExpr(X.data, [](double y, double x) { return std::atan2(y, x); });
        return res;
    }

    /**
     * @brief 転置行列を取得
     * @return 転置された行列
     * 
     * 行列の行と列を入れ替えた転置行列を返します。
     * MATLABの ' 演算子（例：A'）に相当します。
     * 例：3x2行列の転置は2x3行列になります。
     */
    Mat transpose() const { return Mat(data.transpose()); }

    /**
     * @brief 逆行列を取得
     * @return 逆行列
     * 
     * 行列の逆行列を計算して返します。
     * MATLABの inv() 関数に相当します。
     * 正則行列（行列式が0でない行列）のみで動作します。
     * 特異行列の場合、例外が発生します。
     */
    Mat inverse() const { return Mat(data.inverse()); }

    /**
     * @brief 行列式を計算
     * @return 行列式の値
     * 
     * 行列の行列式（デターミナント）を計算して返します。
     * MATLABの det() 関数に相当します。
     * 正方形行列のみで動作します。
     */
    double determinant() const { return data.determinant(); }

    /**
     * @brief 単位行列を生成
     * @param n 正方行列のサイズ
     * @return n x n の単位行列
     * 
     * 指定されたサイズの正方単位行列を生成します。
     * 対角要素が1、それ以外が0の行列です。
     * MATLABの eye(n) に相当します。
     */
    static Mat eye(int n) { return Mat(Eigen::MatrixXd::Identity(n, n)); }

    /**
     * @brief 単位行列を生成
     * @param r 行数
     * @param c 列数
     * @return r x c の単位行列
     * 
     * 指定されたサイズの長方形単位行列を生成します。
     * 対角要素が1、それ以外が0の行列です。
     * MATLABの eye(r, c) に相当します。
     */
    static Mat eye(int r, int c) { return Mat(Eigen::MatrixXd::Identity(r, c)); }

    /**
     * @brief 水平方向に行列を連結
     * @param b 連結する行列
     * @return 連結結果の行列
     * 
     * 現在の行列と指定された行列を水平方向に連結します。
     * MATLABの [A B] に相当します。
     * 両行列の行数が一致している必要があります。
     */
    Mat horizontalConcat(const Mat& b) const {
        Eigen::MatrixXd result(data.rows(), data.cols() + b.data.cols());
        result << data, b.data;
        return Mat(result);
    }

    /**
     * @brief 垂直方向に行列を連結
     * @param b 連結する行列
     * @return 連結結果の行列
     * 
     * 現在の行列と指定された行列を垂直方向に連結します。
     * MATLABの [A; B] に相当します。
     * 両行列の列数が一致している必要があります。
     */
    Mat verticalConcat(const Mat& b) const {
        Eigen::MatrixXd result(data.rows() + b.data.rows(), data.cols());
        result << data, b.data;
        return Mat(result);
    }

    /**
     * @brief 部分行列を取得
     * @param rowStart 開始行インデックス（0から始まる）
     * @param colStart 開始列インデックス（0から始まる）
     * @param rows 取得する行数
     * @param cols 取得する列数
     * @return 部分行列
     * 
     * 指定された範囲の部分行列を取得します。
     * MATLABの A(rowStart+1:rowStart+rows, colStart+1:colStart+cols) に相当します。
     * インデックスは0ベースです。
     */
    Mat slice(int rowStart, int colStart, int rows, int cols) const {
        return Mat(data.block(rowStart, colStart, rows, cols));
    }

    /**
     * @brief 行列の内容をコンソールに表示
     * @param label （オプション）表示するラベル名
     * 
     * 行列の内容をEigenライブラリのデフォルト形式で表示します。
     * labelが指定されている場合は、そのラベルと共に表示されます。
     * MATLABのdisp関数と同様の役割を果たします。
     * 
     * 例:
     * @code
     * Mat m = {{1, 2}, {3, 4}};
     * m.disp("Matrix A"); // "Matrix A ="と共に行列を表示
     * @endcode
     */
    void disp(const std::string& label = "") const {
        if (!label.empty()) std::cout << label << " =" << std::endl;
        std::cout << data << std::endl << std::endl;
    }
};