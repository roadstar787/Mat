# Mat API リファレンス

`Mat` クラスは、Eigenライブラリを基盤とし、MATLABに近い直感的な行列操作を提供するC++クラスです。

## 目次
- [Mat API リファレンス](#mat-api-リファレンス)
  - [目次](#目次)
  - [基本クラス (Mat)](#基本クラス-mat)
    - [コンストラクタ](#コンストラクタ)
    - [基本プロパティ](#基本プロパティ)
    - [要素アクセス](#要素アクセス)
  - [行列演算](#行列演算)
    - [四則演算](#四則演算)
    - [行列積・要素積](#行列積要素積)
  - [線形代数関数](#線形代数関数)
  - [目次](#目次-1)
  - [基本クラス (Mat)](#基本クラス-mat-1)
    - [コンストラクタ](#コンストラクタ-1)
    - [基本プロパティ](#基本プロパティ-1)
    - [要素アクセス](#要素アクセス-1)
  - [行列演算](#行列演算-1)
    - [四則演算](#四則演算-1)
    - [行列積・要素積](#行列積要素積-1)
  - [線形代数関数](#線形代数関数-1)
  - [統計関数](#統計関数)
  - [ユーティリティ関数](#ユーティリティ関数)
  - [乱数生成](#乱数生成)
    - [RandStream クラス](#randstream-クラス)
    - [グローバル関数](#グローバル関数)

---

## 基本クラス (Mat)

### コンストラクタ
| シグネチャ | 説明 | MATLAB相当 |
| :--- | :--- | :--- |
| `Mat()` | 0行0列の空行列を初期化します。 | `[]` |
| `Mat(const Eigen::MatrixXd& m)` | 既存のEigen行列からコピーして作成します。 | - |
| `Mat(int r, int c)` | $r \times c$ のゼロ行列を生成します。 | `zeros(r, c)` |
| `Mat(std::initializer_list<std::initializer_list<double>> list)` | `{{1, 2}, {3, 4}}` 形式で直接定義します。 | `[1, 2; 3, 4]` |

### 基本プロパティ
| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `rows()` | `int` | 行数を返します。 | `size(A, 1)` |
| `cols()` | `int` | 列数を返します。 | `size(A, 2)` |
| `numel()` | `int` | 全要素数を返します。 | `numel(A)` |

### 要素アクセス
- `double& operator()(int r, int c)`: $(r, c)$ 要素への参照（非const版、0-based index）。
- `double operator()(int r, int c) const`: $(r, c)$ 要素の取得（const版、0-based index）。
- `double& operator()(int i)`: 線形インデックス $i$ による要素への参照（非const版、0-based index）。
- `double operator()(int i) const`: 線形インデックス $i$ による要素の取得（const版、0-based index）。

---

## 行列演算

### 四則演算
| 演算子 | 説明 | MATLAB相当 |
| :--- | :--- | :--- |
| `Mat operator+(const Mat& b) const` | 要素ごとの加算 | `A + B` |
| `Mat operator-(const Mat& b) const` | 要素ごとの減算 | `A - B` |
| `Mat operator*(double b) const` | スカラー倍（要素ごとの乗算） | `A * s` |
| `Mat operator/(double b) const` | スカラー除算（要素ごとの除算） | `A / s` |

### 行列積・要素積
| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `Mat mtimes(const Mat& b) const` | `Mat` | 行列積（線形代数的な積）を計算します。 | `A * B` |
| `Mat times(const Mat& b) const` | `Mat` | 要素ごとの乗算（アダマール積）を計算します。 | `A .* B` |

---

## 線形代数関数

| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `Mat transpose() const` | `Mat` | 転置行列を返します。 | `A'` |
| `Mat inverse() const` | `Mat` | 逆行列を計算します（正則行列である必要があります）。 | `inv(A)` |
| `double determinant() const` | `double` | 行列式を計算します。 | `det(A)` |
| `double trace() const` | `double` | 対角要素の和を計算します（正方行列のみ）。 | `trace(A)` |
| `Mat reshape(int newRows, int newCols) const` | `Mat` | 行列の形状を変更します。要素数が一致している必要があります。 | `reshape(A, newRows,<write_to_file>
<path>doc/mat_api_reference.md</path>
<content># Mat API リファレンス

`Mat` クラスは、Eigenライブラリを基盤とし、MATLABに近い直感的な行列操作を提供するC++クラスです。

## 目次
- [Mat API リファレンス](#mat-api-リファレンス)
  - [目次](#目次)
  - [基本クラス (Mat)](#基本クラス-mat)
    - [コンストラクタ](#コンストラクタ)
    - [基本プロパティ](#基本プロパティ)
    - [要素アクセス](#要素アクセス)
  - [行列演算](#行列演算)
    - [四則演算](#四則演算)
    - [行列積・要素積](#行列積要素積)
  - [線形代数関数](#線形代数関数)
  - [目次](#目次-1)
  - [基本クラス (Mat)](#基本クラス-mat-1)
    - [コンストラクタ](#コンストラクタ-1)
    - [基本プロパティ](#基本プロパティ-1)
    - [要素アクセス](#要素アクセス-1)
  - [行列演算](#行列演算-1)
    - [四則演算](#四則演算-1)
    - [行列積・要素積](#行列積要素積-1)
  - [線形代数関数](#線形代数関数-1)
  - [統計関数](#統計関数)
  - [ユーティリティ関数](#ユーティリティ関数)
  - [乱数生成](#乱数生成)
    - [RandStream クラス](#randstream-クラス)
    - [グローバル関数](#グローバル関数)

---

## 基本クラス (Mat)

### コンストラクタ
| シグネチャ | 説明 | MATLAB相当 |
| :--- | :--- | :--- |
| `Mat()` | 0行0列の空行列を初期化します。 | `[]` |
| `Mat(const Eigen::MatrixXd& m)` | 既存のEigen行列からコピーして作成します。 | - |
| `Mat(int r, int c)` | $r \times c$ のゼロ行列を生成します。 | `zeros(r, c)` |
| `Mat(std::initializer_list<std::initializer_list<double>> list)` | `{{1, 2}, {3, 4}}` 形式で直接定義します。 | `[1, 2; 3, 4]` |

### 基本プロパティ
| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `rows()` | `int` | 行数を返します。 | `size(A, 1)` |
| `cols()` | `int` | 列数を返します。 | `size(A, 2)` |
| `numel()` | `int` | 全要素数を返します。 | `numel(A)` |

### 要素アクセス
- `double& operator()(int r, int c)`: $(r, c)$ 要素への参照（非const版、0-based index）。
- `double operator()(int r, int c) const`: $(r, c)$ 要素の取得（const版、0-based index）。
- `double& operator()(int i)`: 線形インデックス $i$ による要素への参照（非const版、0-based index）。
- `double operator()(int i) const`: 線形インデックス $i$ による要素の取得（const版、0-based index）。

---

## 行列演算

### 四則演算
| 演算子 | 説明 | MATLAB相当 |
| :--- | :--- | :--- |
| `Mat operator+(const Mat& b) const` | 要素ごとの加算 | `A + B` |
| `Mat operator-(const Mat& b) const` | 要素ごとの減算 | `A - B` |
| `Mat operator*(double b) const` | スカラー倍（要素ごとの乗算） | `A * s` |
| `Mat operator/(double b) const` | スカラー除算（要素ごとの除算） | `A / s` |

### 行列積・要素積
| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `Mat mtimes(const Mat& b) const` | `Mat` | 行列積（線形代数的な積）を計算します。 | `A * B` |
| `Mat times(const Mat& b) const` | `Mat` | 要素ごとの乗算（アダマール積）を計算します。 | `A .* B` |

---

## 線形代数関数

| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `Mat transpose() const` | `Mat` | 転置行列を返します。 | `A'` |
| `Mat inverse() const` | `Mat` | 逆行列を計算します（正則行列である必要があります）。 | `inv(A)` |
| `double determinant() const` | `double` | 行列式を計算します。 | `det(A)` |
| `double trace() const` | `double` | 対角要素の和を計算します（正方行列のみ）。 | `trace(A)` |
| `Mat reshape(int newRows, int newCols) const` | `Mat` | 行列の形状を変更します。要素数が一致している必要があります。 | `reshape(A, newRows, newCols)` |
| `Mat flipud() const` | `Mat` | 行列を上下反転します。 | `flipud(A)` |
| `Mat fliplr() const` | `Mat` | 行列を左右反転します。 | `fliplr(A)` |
| `Mat rot90(int k = 1) const` | `Mat` | 行列を90度*k*回回転します（時計回り）。 | `rot90(A, k)` |
| `Mat repmat(int m, int n) const` | `Mat` | 行列を*m*×*n*ブロックで繰り返し生成します。 | `repmat(A, m, n)` |
| `static Mat blkdiag(const std::vector<Mat>& matrices)` | `Mat` | ブロック対角行列を生成します。 | `blkdiag(A, B, C, ...)` |
| `Mat triu(int k = 0) const` | `Mat` | 上三角行列を抽出します（*k*は対角線からのオフセット）。 | `triu(A, k)` |
| `Mat tril(int k = 0) const` | `Mat` | 下三角行列を抽出します（*k*は対角線からのオフセット）。 | `tril(A, k)` |
| `Mat diag(int k = 0) const` | `Mat` | 対角要素を抽出します（*k*は対角線からのオフセット）。 | `diag(A, k)` |
| `static Mat diag(const Mat& v, int k = 0)` | `Mat` | ベクトル*v*から対角行列を生成します（*k*は対角線からのオフセット）。 | `diag(v, k)` |

---

## 統計関数

| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `Mat mean(int dim = -1) const` | `Mat` | 各次元における平均を計算します。*dim*が-1の場合は全要素の平均。0は列方向、1は行方向。 | `mean(A, dim)` |
| `Mat std(int dim = -1) const` | `Mat` | 各次元における標準偏差を計算します。*dim*が-1の場合は全要素の標準偏差。0は列方向、1は行方向。 | `std(A, dim)` |
| `Mat sum(int dim = -1) const` | `Mat` | 各次元における合計を計算します。*dim*が-1の場合は全要素の合計。0は列方向、1は行方向。 | `sum(A, dim)` |
| `Mat max(int dim = -1) const` | `Mat` | 各次元における最大値を計算します。*dim*が-1の場合は全要素の最大値。0は列方向、1は行方向。 | `max(A, dim)` |
| `Mat min(int dim = -1) const` | `Mat` | 各次元における最小値を計算します。*dim*が-1の場合は全要素の最小値。0は列方向、1は行方向。 | `min(A, dim)` |
| `Mat median(int dim = -1) const` | `Mat` | 各次元における中央値を計算します。*dim*が-1の場合は全要素の中央値。0は列方向、1は行方向。 | `median(A, dim)` |
| `Mat prod(int dim = -1) const` | `Mat` | 各次元における積を計算します。*dim*が-1の場合は全要素の積。0は列方向、1は行方向。 | `prod(A, dim)` |
| `Mat cumsum(int dim = -1) const` | `Mat` | 各次元における累積和を計算します。*dim*が-1の場合は全要素の累積和。0は列方向、1は行方向。 | `cumsum(A, dim)` |
| `Mat cumprod(int dim = -1) const` | `Mat` | 各次元における累積積を計算します。*dim*が-1の場合は全要素の累積積。0は列方向、1は行方向。 | `cumprod(A, dim)` |
| `double norm(int p = 2) const` | `double` | ベクトルノルムを計算します。*p*が1の場合はL1ノルム、2の場合はL2ノルム、std::numeric_limits<int>::max()の場合はL∞ノルム。 | `norm(A, p)` |

---

## ユーティリティ関数

| 関数名 | 戻り値 | 説明 | MATLAB相当 |
| :--- | :--- | :--- | :--- |
| `Mat horizontalConcat(const Mat& b) const` | `Mat` | 水平方向に連結します。 | `[A, B]` |
| `Mat verticalConcat(const Mat& b) const` | `Mat` | 垂直方向に連結します。 | `[A; B]` |
| `Mat slice(int rowStart, int colStart, int rows, int cols) const` | `Mat` | 行列の一部を切り出します（ブロックアクセス）。 | `A(rowStart:rowStart+rows-1, colStart:colStart+cols-1)` |
| `void disp(const std::string& label = "") const` | `void` | 行列を表示します。ラベルが指定されている場合はそのラベルを付けて表示します。 | `disp(A)` |
| `static Mat linspace(double start, double end, int n)` | `Mat` | *start*から*end*まで*n*個の等間隔の点を持つ行ベクトルを生成します。 | `linspace(start, end, n)` |
| `static Mat range(double start, double step, double end)` | `Mat` | *start*から*end*まで*step*刻みの点を持つ行ベクトルを生成します。 | `start:step:end` |
| `static Mat find(const Mat& condition)` | `Mat` | 条件を満たす要素の線形インデックスを返します（0-based）。 | `find(condition)` |
| `static std::pair<Mat, Mat> find2d(const Mat& condition)` | `pair<Mat, Mat>` | 条件を満たす要素の行と列のインデックスを返します（1-based、MATLAB互換）。 | `[i, j] = find(condition)` |
| `static Mat diff(const Mat& A)` | `Mat` | 要素間の差分を計算します。ベクトルの場合は後方差分、行列の場合は行方向の差分。 | `diff(A)` |
| `static Mat movmean(const Mat& A, int k)` | `Mat` | 指定された窓サイズ*k*で移動平均を計算します。 | `movmean(A, k)` |
| `static Mat atan2(const Mat& Y, const Mat& X)` | `Mat` | 要素ごとのatan2を計算します。 | `atan2(Y, X)` |
| `static Mat ones(int r, int c)` | `Mat` | *r*×*c*のすべての要素が1の行列を生成します。 | `ones(r, c)` |
| `static Mat zeros(int r, int c)` | `Mat` | *r*×*c*のすべての要素が0の行列を生成します。 | `zeros(r, c)` |
| `static Mat eye(int n)` | `Mat` | *n*×*n*の単位行列を生成します。 | `eye(n)` |
| `static Mat eye(int r, int c)` | `Mat` | *r*×*c*の単位行列を生成します（対角要素が1、それ以外は0）。 | `eye(r, c)` |

---

## 乱数生成

### RandStream クラス
| シグネチャ | 説明 |
| :--- | :--- |
| `RandStream()` | デフォルトコンストラクタ。現在時刻をシードとして使用します。 |
| `RandStream(unsigned int seed)` | シードを指定するコンストラクタ。 |
| `Mat uniform(int rows, int cols)` | 一様乱数を生成します（値の範囲は[0,1)）。 |
| `Mat uniform(int rows, int cols, double min, double max)` | 指定範囲の一様乱数を生成します（値の範囲は[min,max)）。 |
| `Mat normal(int rows, int cols)` | 正規乱数を生成します（平均0、標準偏差1）。 |
| `void setSeed(unsigned int seed)` | シードを設定します。 |
| `unsigned int getSeed() const` | 現在のシードを取得します。 |

### グローバル関数
| シグネチャ | 説明 |
| :--- | :--- |
| `Mat rand(int rows, int cols)` | 一様乱数を生成します（範囲: [0, 1)）。 |
| `Mat rand(int rows, int cols, double min, double max)` | 指定範囲の一様乱数を生成します（範囲: [min, max)）。 |
| `Mat randn(int rows, int cols)` | 正規乱数を生成します（平均: 0, 標準偏差: 1）。 |
| `void setRandomSeed(unsigned int seed)` | グローバルな乱数ストリームのシードを設定します。 |
| `unsigned int getRandomSeed()` | グローバルな乱数ストリームの現在のシードを取得します。 |

---
*このドキュメントは、`src/mat` ディレクトリのソースコードに基づいて生成されました。*