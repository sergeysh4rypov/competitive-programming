/**
 * Dijkstra's Algorithm
 * Purpose: Finds the shortest paths from a source vertex to all others in a weighted graph.
 * Complexity: O(E log V) using a priority queue.
 * Note: Works only with non-negative edge weights.
 */

#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

struct Edge {
    int to;
    int weight;
};

/**
 * @param start_node - начальная вершина
 * @param adj - список смежности: adj[u] содержит список структур Edge {v, weight}
 * @return vector<long long> - кратчайшие расстояния до всех вершин
 */
vector<long long> dijkstra(int n, int start_node, const vector<vector<Edge>>& adj) {
    vector<long long> dist(n, INF);
    dist[start_node] = 0;

    // Храним пары {расстояние, вершина}. 
    // priority_queue в C++ по умолчанию — это max-heap, 
    // поэтому используем greater<>, чтобы сделать min-heap.
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    pq.push({0, start_node});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Важная проверка: если мы уже нашли путь короче, игнорируем старую запись в куче
        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
