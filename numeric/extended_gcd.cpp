/**
 * Extended Euclidean Algorithm
 * Finds gcd(a, b) and coefficients x, y such that ax + by = gcd(a, b).
 * Also used to find modular multiplicative inverse.
 */

#include <tuple>
#include <iostream>

using namespace std;

/**
 * Рекурсивная реализация
 * Сложность: O(log(min(a, b)))
 * Возвращает {gcd, x, y}
 */
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

/**
 * Поиск обратного элемента по модулю (Modular Inverse)
 * Находит x такой, что (a * x) % m == 1.
 * Работает, если gcd(a, m) == 1.
 * В отличие от метода Ферма, работает и для составных модулей m.
 */
long long mod_inverse(long long a, long long m) {
    long long x, y;
    long long g = extended_gcd(a, m, x, y);
    if (g != 1) {
        return -1; // Обратного элемента не существует
    }
    // В C++ результат % может быть отрицательным, приводим к положительному
    return (x % m + m) % m;
}

/**
 * Пример использования для проверки корректности
 */
void test_gcd() {
    long long a = 19, b = 7, x, y;
    long long g = extended_gcd(a, b, x, y);
    // 19*(2) + 7*(-5) = 38 - 35 = 3 (gcd=1 для 19 и 7)
    // Для 19 и 7: 19*(-3) + 7*(8) = -57 + 56 = -1, значит 19*(3) + 7*(-8) = 1
}
