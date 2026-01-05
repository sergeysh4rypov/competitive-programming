/**
 * Rolling Hash (Double Hash)
 * Purpose: Compare substrings in O(1) and find patterns.
 * Complexity: O(N) preprocessing, O(1) query.
 */

#include <vector>
#include <string>

using namespace std;

class StringHash {
    int n;
    long long mod1 = 1e9 + 7, mod2 = 1e9 + 9;
    long long base1 = 31, base2 = 37;
    vector<long long> h1, h2, p1, p2;

public:
    StringHash(const string& s) : n(s.size()) {
        h1.resize(n + 1, 0); h2.resize(n + 1, 0);
        p1.resize(n + 1, 1); p2.resize(n + 1, 1);

        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * base1 + (s[i] - 'a' + 1)) % mod1;
            h2[i + 1] = (h2[i] * base2 + (s[i] - 'a' + 1)) % mod2;
            p1[i + 1] = (p1[i] * base1) % mod1;
            p2[i + 1] = (p2[i] * base2) % mod2;
        }
    }

    // Возвращает хеш подстроки s[l..r] (0-indexed)
    pair<long long, long long> get_hash(int l, int r) {
        long long res1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % mod1 + mod1) % mod1;
        long long res2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % mod2 + mod2) % mod2;
        return {res1, res2};
    }
};
