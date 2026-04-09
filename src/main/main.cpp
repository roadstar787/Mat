int main() {
    // 1. 初期化
    Mat A = {{1, 2, 3}, {4, 5, 6}};
    Mat B = Mat::ones(2, 3);

    // 2. 四則演算
    Mat C = A + B;       // 要素ごとの加算
    Mat D = A.times(B);  // A .* B

    // 3. ベクトル演算
    Mat v = {{10, 20, 40, 70}};
    Mat dv = Mat::diff(v); // [10, 20, 30]
    
    // 4. 移動平均
    Mat m = Mat::movmean(v, 3);

    // 5. 数学関数
    Mat y = {{1.0, 0.0}};
    Mat x = {{0.0, 1.0}};
    Mat theta = Mat::atan2(y, x); // [pi/2, 0]

    C.disp("C");
    dv.disp("diff(v)");
    theta.disp("atan2(y,x)");

    return 0;
}