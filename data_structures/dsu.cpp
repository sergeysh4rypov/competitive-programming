/**
 * Disjoint Set Union (DSU) / Union-Find
 * Efficiently manages a partition of a set into disjoint subsets.
 * Optimizations: Path Compression and Union by Rank/Size.
 * Time Complexity: Nearly O(1) amortized per operation.
 */

#include <vector>
#include <numeric>

using namespace std;

class DSU {
    vector<int> parent;
    vector<int> group_size;
    int num_components;

public:
    DSU(int n) : num_components(n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0); // Изначально каждый элемент — сам себе родитель
        group_size.assign(n, 1);
    }

    // Нахождение представителя множества с оптимизацией сжатия пути (Path Compression)
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Переподвешиваем вершину напрямую к корню
    }

    // Объединение двух множеств с оптимизацией по размеру (Union by Size)
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            // Подвешиваем меньшее дерево к большему, чтобы глубина росла медленнее
            if (group_size[root_i] < group_size[root_j])
                swap(root_i, root_j);
            
            parent[root_j] = root_i;
            group_size[root_i] += group_size[root_j];
            num_components--;
            return true; // Множества были разными и успешно объединились
        }
        return false; // Уже в одном множестве
    }

    int size(int i) {
        return group_size[find(i)];
    }

    int components() const {
        return num_components;
    }
};
