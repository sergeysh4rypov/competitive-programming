/**
 * Number Theoretic Transform (NTT)
 * Power-of-two length FFT using modular arithmetic.
 * Modulo 998244353 is a "NTT-friendly" prime: 998244353 = 119 * 2^23 + 1.
 */

#include <vector>
#include <algorithm>

using namespace std;

class NTT {
    const int MOD = 998244353;
    const int G = 3; // Primitive root modulo 998244353

    long long power(long long a, long long b) {
        long long res = 1;
        a %= MOD;
        while (b > 0) {
            if (b & 1) res = (res * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

public:
    void transform(vector<int>& a, bool invert) {
        int n = a.size();
        // Bit-reversal permutation
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        // Butterfly operations
        for (int len = 2; len <= n; len <<= 1) {
            long long wlen = power(G, (MOD - 1) / len);
            if (invert) wlen = modInverse(wlen);
            for (int i = 0; i < n; i += len) {
                long long w = 1;
                for (int j = 0; j < len / 2; j++) {
                    int u = a[i + j], v = (1LL * a[i + j + len / 2] * w) % MOD;
                    a[i + j] = (u + v) % MOD;
                    a[i + j + len / 2] = (u - v + MOD) % MOD;
                    w = (w * wlen) % MOD;
                }
            }
        }

        if (invert) {
            long long n_inv = modInverse(n);
            for (int& x : a) x = (1LL * x * n_inv) % MOD;
        }
    }

    // Main function to multiply two polynomials
    vector<int> multiply(vector<int> a, vector<int> b) {
        int n = 1;
        int target = a.size() + b.size();
        while (n < target) n <<= 1;
        
        a.resize(n);
        b.resize(n);
        
        transform(a, false);
        transform(b, false);
        for (int i = 0; i < n; i++) {
            a[i] = (1LL * a[i] * b[i]) % MOD;
        }
        transform(a, true);
        
        // Optional: shrink to actual size
        while (a.size() > 1 && a.back() == 0) a.pop_back();
        return a;
    }
};
