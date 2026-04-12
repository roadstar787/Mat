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

     /**
      * @brief 線形スペースを生成（ベクトル）
      * @param start 開始値
      * @param end 終了値
      * @param n 生成する要素数
      * @return startからendまで均等に分割されたn要素の行ベクトル
      * 
      * MATLABの linspace(start, end, n) に相当します。
      * nが1以下の場合は空のベクトルを返します。
      */
     static Mat linspace(double start, double end, int n) {
         if (n <= 0) return Mat(1, 0);
         if (n == 1) return Mat({{start}});
         
         Mat result(1, n);
         double step = (end - start) / (n - 1);
         for (int i = 0; i < n; ++i) {
             result(0, i) = start + i * step;
         }
         return result;
     }

     /**
      * @brief ステップサイズを指定して範囲を生成（ベクトル）
      * @param start 開始値
      * @param step ステップサイズ
      * @param end 終了値（この値を含まないか、含むかはステップの方向による）
      * @return startからstepずつ増加させた要素の行ベクトル
      * 
      * MATLABの start:step:end に相当します。
      * stepが0の場合は空のベクトルを返します。
      */
     static Mat range(double start, double step, double end) {
         if (step == 0.0) return Mat(1, 0);
         
         std::vector<double> values;
         if (step > 0) {
             for (double val = start; val <= end; val += step) {
                 values.push_back(val);
             }
         } else {
             for (double val = start; val >= end; val += step) {
                 values.push_back(val);
             }
         }
         
         Mat result(1, static_cast<int>(values.size()));
         for (size_t i = 0; i < values.size(); ++i) {
             result(0, static_cast<int>(i)) = values[i];
         }
         return result;
     }
     };

     /**
      * @brief 平均値を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での平均値（ベクトルまたはスカラー）
      * 
      * MATLABの mean(A, dim) に相当します。
      * dimが指定されていない場合は全要素の平均を返します。
      */
     Mat mean(int dim = -1) const {
         if (dim == -1) { // 全要素の平均
             return Mat({{data.mean()}});
         } else if (dim == 0) { // 行方向の平均（各列の平均）
             return Mat(1, cols(), data.colwise().mean());
         } else if (dim == 1) { // 列方向の平均（各行の平均）
             return Mat(rows(), 1, data.rowwise().mean());
         } else {
             return Mat({{data.mean()}}); // デフォルトは全要素の平均
         }
     }

     /**
      * @brief 標準偏差を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での標準偏差（ベクトルまたはスカラー）
      * 
      * MATLABの std(A, dim) に相当します。
      * dimが指定されていない場合は全要素の標準偏差を返します。
      */
     Mat std(int dim = -1) const {
         if (dim == -1) { // 全要素の標準偏差
             return Mat({{data.stddev()}});
         } else if (dim == 0) { // 行方向の標準偏差（各列の標準偏差）
             return Mat(1, cols(), data.colwise().stddev());
         } else if (dim == 1) { // 列方向の標準偏差（各行の標準偏差）
             return Mat(rows(), 1, data.rowwise().stddev());
         } else {
             return Mat({{data.stddev()}}); // デフォルトは全要素の標準偏差
         }
     }

     /**
      * @brief 合計を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での合計（ベクトルまたはスカラー）
      * 
      * MATLABの sum(A, dim) に相当します。
      * dimが指定されていない場合は全要素の合計を返します。
      */
     Mat sum(int dim = -1) const {
         if (dim == -1) { // 全要素の合計
             return Mat({{data.sum()}});
         } else if (dim == 0) { // 行方向の合計（各列の合計）
             return Mat(1, cols(), data.colwise().sum());
         } else if (dim == 1) { // 列方向の合計（各行の合計）
             return Mat(rows(), 1, data.rowwise().sum());
         } else {
             return Mat({{data.sum()}}); // デフォルトは全要素の合計
         }
     }

     /**
      * @brief 最大値を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での最大値（ベクトルまたはスカラー）
      * 
      * MATLABの max(A, dim) に相当します。
      * dimが指定されていない場合は全要素の最大値を返します。
      */
     Mat max(int dim = -1) const {
         if (dim == -1) { // 全要素の最大値
             return Mat({{data.maxCoeff()}});
         } else if (dim == 0) { // 行方向の最大値（各列の最大値）
             return Mat(1, cols(), data.colwise().maxCoeff());
         } else if (dim == 1) { // 列方向の最大値（各行の最大値）
             return Mat(rows(), 1, data.rowwise().maxCoeff());
         } else {
             return Mat({{data.maxCoeff()}}); // デフォルトは全要素の最大値
         }
     }

     /**
      * @brief 最小値を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での最小値（ベクトルまたはスカラー）
      * 
      * MATLABの min(A, dim) に相当します。
      * dimが指定されていない場合は全要素の最小値を返します。
      */
     Mat min(int dim = -1) const {
         if (dim == -1) { // 全要素の最小値
             return Mat({{data.minCoeff()}});
         } else if (dim == 0) { // 行方向の最小値（各列の最小値）
             return Mat(1, cols(), data.colwise().minCoeff());
         } else if (dim == 1) { // 列方向の最小値（各行の最小値）
             return Mat(rows(), 1, data.rowwise().minCoeff());
         } else {
             return Mat({{data.minCoeff()}}); // デフォルトは全要素の最小値
         }
     }

     /**
      * @brief 中央値を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での中央値（ベクトルまたはスカラー）
      * 
      * MATLABの median(A, dim) に相当します。
      * dimが指定されていない場合は全要素の中央値を返します。
      */
     Mat median(int dim = -1) const {
         if (dim == -1) { // 全要素の中央値
             Eigen::VectorXd flat = data;
             std::sort(flat.data(), flat.data() + flat.size());
             size_t n = flat.size();
             if (n == 0) return Mat({{0.0}});
             if (n % 2 == 0) {
                 return Mat({{(flat(n/2 - 1) + flat(n/2)) / 2.0}});
             } else {
                 return Mat({{flat(n/2)}});
             }
         } else if (dim == 0) { // 行方向の中央値（各列の中央値）
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
         } else if (dim == 1) { // 列方向の中央値（各行の中央値）
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
             return median(); // デフォルトは全要素の中央値
         }
     }

     /**
      * @brief 積を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での積（ベクトルまたはスカラー）
      * 
      * MATLABの prod(A, dim) に相当します。
      * dimが指定されていない場合は全要素の積を返します。
      */
     Mat prod(int dim = -1) const {
         if (dim == -1) { // 全要素の積
             return Mat({{data.prod()}});
         } else if (dim == 0) { // 行方向の積（各列の積）
             return Mat(1, cols(), data.colwise().prod());
         } else if (dim == 1) { // 列方向の積（各行の積）
             return Mat(rows(), 1, data.rowwise().prod());
         } else {
             return Mat({{data.prod()}}); // デフォルトは全要素の積
         }
     }

     /**
      * @brief 累積和を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での累積和（ベクトルまたは行列）
      * 
      * MATLABの cumsum(A, dim) に相当します。
      * dimが指定されていない場合は全要素の累積和を返します。
      */
     Mat cumsum(int dim = -1) const {
         if (dim == -1) { // 全要素の累積和
             Eigen::VectorXd flat = data;
             Eigen::VectorXd cumsum(flat.size());
             double sum = 0.0;
             for (int i = 0; i < flat.size(); ++i) {
                 sum += flat(i);
                 cumsum(i) = sum;
             }
             return Mat(cumsum);
         } else if (dim == 0) { // 行方向の累積和（各列の累積和）
             return Mat(data.colwise().cumsum());
         } else if (dim == 1) { // 列方向の累積和（各行の累積和）
             return Mat(data.rowwise().cumsum());
         } else {
             return cumsum(); // デフォルトは全要素の累積和
         }
     }

     /**
      * @brief 累積積を計算（次元指定対応）
      * @param dim 次元（0で行方向、1で列方向、-1で全要素）
      * @return 指定次元での累積積（ベクトルまたは行列）
      * 
      * MATLABの cumprod(A, dim) に相当します。
      * dimが指定されていない場合は全要素の累積積を返します。
      */
     Mat cumprod(int dim = -1) const {
         if (dim == -1) { // 全要素の累積積
             Eigen::VectorXd flat = data;
             Eigen::VectorXd cumprod(flat.size());
             double prod = 1.0;
             for (int i = 0; i < flat.size(); ++i) {
                 prod *= flat(i);
                 cumprod(i) = prod;
             }
             return Mat(cumprod);
         } else if (dim == 0) { // 行方向の累積積（各列の累積積）
             return Mat(data.colwise().cumprod());
         } else if (dim == 1) { // 列方向の累積積（各行の累積積）
             return Mat(data.rowwise().cumprod());
         } else {
             return cumprod(); // デフォルトは全要素の累積積
         }
     }

     /**
      * @brief 2つのベクトルの内積（ドット積）を計算
      * @param b 内積を計算するベクトル
      * @return 内積の結果（スカラー）
      * 
      * MATLABの dot(A, B) に相当します。
      * 両方ともベクトル（1行または1列）である必要があります。
      * 次元が一致している必要があります。
      */
     Mat dot(const Mat& b) const {
         if ((rows() == 1 || cols() == 1) && (b.rows() == 1 || b.cols() == 1)) {
             // 両方ともベクトルであることを確認
             if (numel() == b.numel()) {
                 return Mat({{data.dot(b.data)}});
             }
         }
         // 条件を満たさない場合は0を返す（または例外を投げることも可能）
         return Mat({{0.0}});
     }

     /**
      * @brief 2つの3次元ベクトルの外積（クロス積）を計算
      * @param b 外積を計算するベクトル
      * @return 外積の結果（3次元ベクトル）
      * 
      * MATLABの cross(A, B) に相当します。
      * 両方とも3次元ベクトルである必要があります。
      */
     Mat cross(const Mat& b) const {
         if ((rows() == 3 && cols() == 1) || (rows() == 1 && cols() == 3)) {
             if ((b.rows() == 3 && b.cols() == 1) || (b.rows() == 1 && b.cols() == 3)) {
                 // 両方とも3次元ベクトルであることを確認
                 Eigen::Vector3d a_vec, b_vec;
                 
                 // 自身のベクトルを取得
                 if (rows() == 3) {
                     a_vec << data(0, 0), data(1, 0), data(2, 0);
                 } else {
                     a_vec << data(0, 0), data(0, 1), data(0, 2);
                 }
                 
                 // 引数のベクトルを取得
                 if (b.rows() == 3) {
                     b_vec << b.data(0, 0), b.data(1, 0), b.data(2, 0);
                 } else {
                     b_vec << b.data(0, 0), b.data(0, 1), b.data(0, 2);
                 }
                 
                 // 外積を計算
                 Eigen::Vector3d result_vec = a_vec.cross(b_vec);
                 
                 // 結果をベクトル形式で返す（列ベクトルとして）
                 Mat result(3, 1);
                 result << result_vec(0), result_vec(1), result_vec(2);
                 return result;
             }
         }
         // 条件を満たさない場合はゼロベクトルを返す
         return Mat::zeros(3, 1);
     }

     // === 追加のベクトル・行列関数 ===

     /**
      * @brief 行列の跡（trace）を計算
      * @return 跡の値（対角要素の和）
      * 
      * MATLABの trace(A) に相当します。
      * 正方形行列のみで動作します。
      */
     double trace() const {
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
      * p = 1: 1-ノルム（絶対値の和）
      * p = 2: 2-ノルム（ユークリッドノルム）
      * p = infinity: 無限大ノルム（最大絶対値）
      */
     double norm(int p = 2) const {
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

     /**
      * @brief 行列の形を変更
      * @param newRows 新しい行数
      * @param newCols 新しい列数
      * @return 形状が変更された行列
      * 
      * MATLABの reshape(A, m, n) に相当します。
      * 要素数が一致している必要があります。
      */
     Mat reshape(int newRows, int newCols) const {
         if (newRows * newCols != numel()) {
             throw std::invalid_argument("Reshape dimensions must match total number of elements");
         }
         return Mat(data.reshaped<Eigen::RowMajor>(newRows, newCols));
     }

     /**
      * @brief 行列を上下反転
      * @return 反転された行列
      * 
      * MATLABの flipud(A) に相当します。
      */
     Mat flipud() const {
         return Mat(data.reverse());
     }

     /**
      * @brief 行列を左右反転
      * @return 反転された行列
      * 
      * MATLABの fliplr(A) に相当します。
      */
     Mat fliplr() const {
         return Mat(data.rowwise().reverse());
     }

     /**
      * @brief 行列を90度回転
      * @param k 回転の回数（90度単位、正の値は時計回り）
      * @return 回転された行列
      * 
      * MATLABの rot90(A, k) に相当します。
      */
     Mat rot90(int k = 1) const {
         Mat result = *this;
         for (int i = 0; i < (k % 4); ++i) {
             result = result.transpose().fliplr();
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
     Mat repmat(int m, int n) const {
         if (m <= 0 || n <= 0) return Mat();
         
         Mat result(rows() * m, cols() * n);
         for (int i = 0; i < m; ++i) {
             for (int j = 0; j < n; ++j) {
                 result.block(i * rows(), j * cols(), rows(), cols()) = data;
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
     static Mat blkdiag(const std::vector<Mat>& matrices) {
         if (matrices.empty()) return Mat();
         
         int totalRows = 0, totalCols = 0;
         for (const auto& mat : matrices) {
             totalRows += mat.rows();
             totalCols += mat.cols();
         }
         
         Mat result(totalRows, totalCols);
         int currentRow = 0, currentCol = 0;
         
         for (const auto& mat : matrices) {
             result.block(currentRow, currentCol, mat.rows(), mat.cols()) = mat.data;
             currentRow += mat.rows();
             currentCol += mat.cols();
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
     Mat triu(int k = 0) const {
         Mat result = *this;
         for (int i = 0; i < rows(); ++i) {
             for (int j = 0; j < cols(); ++j) {
                 if (j < i + k) {
                     result(i, j) = 0.0;
                 }
             }
         }
         return result;
     }

     /**
      * @brief 下三角行列を抽出
      * @param k 対角線からのオフセット（0が主対角線）
      * @return 下三角行列
      * 
      * MATLABの tril(A, k) に相当します。
      */
     Mat tril(int k = 0) const {
         Mat result = *this;
         for (int i = 0; i < rows(); ++i) {
             for (int j = 0; j < cols(); ++j) {
                 if (j > i + k) {
                     result(i, j) = 0.0;
                 }
             }
         }
         return result;
     }

     /**
      * @brief 対角要素を抽出または生成
      * @param k 対角線からのオフセット（0が主対角線）
      * @return 対角要素からなるベクトル
      * 
      * MATLABの diag(A, k) に相当します。
      */
     Mat diag(int k = 0) const {
         std::vector<double> diagonal;
         if (k >= 0) {
             int maxDiag = std::min(rows(), cols() - k);
             for (int i = 0; i < maxDiag; ++i) {
                 diagonal.push_back(data(i, i + k));
             }
         } else {
             int maxDiag = std::min(rows() + k, cols());
             for (int i = 0; i < maxDiag; ++i) {
                 diagonal.push_back(data(i - k, i));
             }
         }
         
         Mat result(static_cast<int>(diagonal.size()), 1);
         for (size_t i = 0; i < diagonal.size(); ++i) {
             result(i, 0) = diagonal[i];
         }
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
     static Mat diag(const Mat& v, int k = 0) {
         int size = v.rows() * v.cols();
         int matSize = size + std::abs(k);
         Mat result(matSize, matSize);
         
         int idx = 0;
         if (k >= 0) {
             for (int i = 0; i < size; ++i) {
                 result(i, i + k) = v(idx++);
             }
         } else {
             for (int i = 0; i < size; ++i) {
                 result(i - k, i) = v(idx++);
             }
         }
         
         return result;
     }

     // === 論理インデックス関数 ===

     /**
      * @brief 論理インデックスで要素を検索
      * @param condition 論理行列（true/false）
      * @return 見つかった要素のインデックスのベクトル
      * 
      * MATLABの find(condition) に相当します。
      */
     static Mat find(const Mat& condition) {
         std::vector<int> indices;
         indices.reserve(condition.numel());
         
         for (int i = 0; i < condition.rows(); ++i) {
             for (int j = 0; j < condition.cols(); ++j) {
                 if (condition(i, j) != 0.0) { // 0でないものをtrueとみなす
                     // 線形インデックスを計算
                     indices.push_back(i * condition.cols() + j);
                 }
             }
         }
         
         // インデックスを列ベクトルとして返す
         Mat result(static_cast<int>(indices.size()), 1);
         for (size_t k = 0; k < indices.size(); ++k) {
             result(k, 0) = static_cast<double>(indices[k]);
         }
         
         return result;
     }

     /**
      * @brief 論理インデックスで要素を検索（行と列のペア）
      * @param condition 論理行列（true/false）
      * @return 見つかった要素の行インデックスと列インデックスのペア
      * 
      * MATLABの [row, col] = find(condition) に相当します。
      */
     static std::pair<Mat, Mat> find2d(const Mat& condition) {
         std::vector<int> rowIndices, colIndices;
         rowIndices.reserve(condition.numel());
         colIndices.reserve(condition.numel());
         
         for (int i = 0; i < condition.rows(); ++i) {
             for (int j = 0; j < condition.cols(); ++j) {
                 if (condition(i, j) != 0.0) { // 0でないものをtrueとみなす
                     rowIndices.push_back(i + 1); // MATLABは1ベース
                     colIndices.push_back(j + 1); // MATLABは1ベース
                 }
             }
         }
         
         // 行インデックスと列インデックスを返す
         Mat rows(static_cast<int>(rowIndices.size()), 1);
         Mat cols(static_cast<int>(colIndices.size()), 1);
         
         for (size_t k = 0; k < rowIndices.size(); ++k) {
             rows(k, 0) = static_cast<double>(rowIndices[k]);
             cols(k, 0) = static_cast<double>(colIndices[k]);
         }
         
         return {rows, cols};
     }
};