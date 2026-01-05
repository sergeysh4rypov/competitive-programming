/**
 * Z-function
 * z[i] is the length of the longest common prefix between s and s[i..n-1].
 * Complexity: O(N)
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n);
    // [l, r] — границы самого правого найденного совпадения с префиксом
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
