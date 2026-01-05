/**
 * Linear Sieve and Fast Factorization
 * Complexity: O(N) for preprocessing, O(log X) for each factorization.
 * This implementation precomputes the smallest prime factor (SPF) for each number.
 */

#include <vector>
#include <map>

using namespace std;

struct Sieve {
    int n;
    vector<int> min_prime; // Smallest Prime Factor (SPF)
    vector<int> primes;

    // Конструктор: строит решето до числа n за O(n)
    Sieve(int n) : n(n), min_prime(n + 1, 0) {
        for (int i = 2; i <= n; ++i) {
            if (min_prime[i] == 0) {
                min_prime[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > min_prime[i] || 1LL * i * p > n) break;
                min_prime[i * p] = p;
            }
        }
    }

    // Быстрая проверка на простоту за O(1)
    bool is_prime(int x) const {
        if (x < 2 || x > n) return false;
        return min_prime[x] == x;
    }

    // Факторизация за O(log x)
    // Возвращает список простых множителей: 12 -> {2, 2, 3}
    vector<int> factorize(int x) const {
        vector<int> factors;
        while (x > 1) {
            factors.push_back(min_prime[x]);
            x /= min_prime[x];
        }
        return factors;
    }

    // Факторизация с группировкой: 12 -> {{2, 2}, {3, 1}} (т.е. 2^2 * 3^1)
    map<int, int> factorize_grouped(int x) const {
        map<int, int> counts;
        while (x > 1) {
            counts[min_prime[x]]++;
            x /= min_prime[x];
        }
        return counts;
    }
};
