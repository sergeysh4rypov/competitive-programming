/**
 * Topological Sort (using DFS)
 * Purpose: Orders vertices of a Directed Acyclic Graph (DAG) such that 
 * for every directed edge u -> v, vertex u comes before v.
 * Complexity: O(V + E)
 */

#include <vector>
#include <algorithm>

using namespace std;

class TopSort {
    int n;
    vector<vector<int>> adj;
    vector<int> visited; // 0: unvisited, 1: visiting, 2: visited
    vector<int> order;
    bool has_cycle = false;

    void dfs(int u) {
        visited[u] = 1; // Помечаем как "в процессе" (серый цвет)
        for (int v : adj[u]) {
            if (visited[v] == 0) {
                dfs(v);
            } else if (visited[v] == 1) {
                has_cycle = true; // Наткнулись на вершину в стеке — нашли цикл
            }
            if (has_cycle) return;
        }
        visited[u] = 2; // Помечаем как "полностью обработана" (черный цвет)
        order.push_back(u);
    }

public:
    TopSort(int n, const vector<vector<int>>& adjacency_list) 
        : n(n), adj(adjacency_list), visited(n, 0) {}

    /**
     * @return {true, order} если граф ацикличен, {false, {}} если найден цикл.
     */
    pair<bool, vector<int>> get_order() {
        order.clear();
        fill(visited.begin(), visited.end(), 0);
        has_cycle = false;

        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                dfs(i);
            }
        }

        if (has_cycle) return {false, {}};

        reverse(order.begin(), order.end());
        return {true, order};
    }
};
