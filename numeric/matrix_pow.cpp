/**
 * Matrix Exponentiation
 * Purpose: Computes A^n in O(K^3 log N) time, where K is matrix size.
 * Common use: Finding N-th Fibonacci number or solving linear recurrences.
 */

#include <vector>
#include <iostream>

using namespace std;

template<typename T>
struct Matrix {
    int rows, cols;
    vector<vector<T>> mat;
    T mod;

    Matrix(int r, int c, T m) : rows(r), cols(c), mod(m), mat(r, vector<T>(c, 0)) {}

    // Создание единичной матрицы
    static Matrix identity(int n, T m) {
        Matrix res(n, n, m);
        for (int i = 0; i < n; i++) res.mat[i][i] = 1;
        return res;
    }

    // Перегрузка умножения для удобства: A * B
    Matrix operator*(const Matrix& other) const {
        Matrix res(rows, other.cols, mod);
        for (int i = 0; i < rows; i++) {
            for (int k = 0; k < cols; k++) {
                if (mat[i][k] == 0) continue; // Оптимизация для разреженных матриц
                for (int j = 0; j < other.cols; j++) {
                    res.mat[i][j] = (res.mat[i][j] + 1LL * mat[i][k] * other.mat[k][j]) % mod;
                }
            }
        }
        return res;
    }
};

// Функция быстрого возведения в степень
template<typename T>
Matrix<T> power(Matrix<T> a, long long b) {
    Matrix<T> res = Matrix<T>::identity(a.rows, a.mod);
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

/**
 * Пример: Нахождение N-го числа Фибоначчи за O(log N)
 * F(n) = 1*F(n-1) + 1*F(n-2)
 * Матрица перехода: {{1, 1}, {1, 0}}
 */
long long get_fibonacci(long long n, long long mod) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    Matrix<long long> T(2, 2, mod);
    T.mat = {{1, 1}, {1, 0}};
    
    T = power(T, n - 1);
    return T.mat[0][0]; // Результат умножения на базовый вектор {F1, F0}
}
