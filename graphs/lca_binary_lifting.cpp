/**
 * Lowest Common Ancestor (LCA) using Binary Lifting
 * Preprocessing: O(N log N)
 * Query: O(log N)
 */

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class LCA {
    int n;
    int l; // log2(n)
    vector<vector<int>> adj;
    vector<int> tin, tout;
    vector<vector<int>> up;
    int timer;

    void dfs(int v, int p) {
        tin[v] = ++timer;
        up[v][0] = p; // предок 2^0 = 1
        for (int i = 1; i <= l; ++i) {
            // предок 2^i — это предок 2^(i-1) от предка 2^(i-1)
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (int to : adj[v]) {
            if (to != p) {
                dfs(to, v);
            }
        }
        tout[v] = ++timer;
    }

    // Проверка: является ли u предком v за O(1)
    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

public:
    LCA(int n, int root, const vector<vector<int>>& adjacency_list) {
        this->n = n;
        this->adj = adjacency_list;
        this->l = ceil(log2(n));
        tin.resize(n);
        tout.resize(n);
        up.assign(n, vector<int>(l + 1));
        timer = 0;
        
        // Начинаем DFS, считая предком корня сам корень
        dfs(root, root);
    }

    int get_lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }
};
