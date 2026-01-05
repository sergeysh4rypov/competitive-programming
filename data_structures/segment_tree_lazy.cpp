/**
 * Dynamic Segment Tree with Lazy Propagation (Pointer-based)
 * Supports: Range Update (Add) and Range Query (Sum) on huge ranges [0, 10^9].
 * Memory: O(Q log N) where Q is number of queries.
 */

#include <iostream>

using namespace std;

struct Node {
    long long sum;
    long long lazy;
    Node *l, *r;

    Node() : sum(0), lazy(0), l(nullptr), r(nullptr) {}

    // Метод для безопасного получения суммы ребенка
    long long get_sum(Node* node) {
        return node ? node->sum : 0;
    }

    // Проталкивание обновлений
    void push(long long tl, long long tr) {
        if (!l) l = new Node();
        if (!r) r = new Node();
        if (lazy != 0) {
            long long tm = tl + (tr - tl) / 2;
            
            // Левый ребенок
            l->sum += lazy * (tm - tl + 1);
            l->lazy += lazy;
            
            // Правый ребенок
            r->sum += lazy * (tr - tm);
            r->lazy += lazy;
            
            lazy = 0; // Сбрасываем текущий lazy
        }
    }

    void update(long long tl, long long tr, long long ql, long long qr, long long add) {
        if (ql > qr) return;
        if (ql == tl && qr == tr) {
            sum += add * (tr - tl + 1);
            lazy += add;
            return;
        }
        push(tl, tr);
        long long tm = tl + (tr - tl) / 2;
        l->update(tl, tm, ql, min(qr, tm), add);
        r->update(tm + 1, tr, max(ql, tm + 1), qr, add);
        sum = l->sum + r->sum;
    }

    long long query(long long tl, long long tr, long long ql, long long qr) {
        if (ql > qr) return 0;
        if (ql == tl && qr == tr) return sum;
        push(tl, tr);
        long long tm = tl + (tr - tl) / 2;
        return l->query(tl, tm, ql, min(qr, tm)) +
               r->query(tm + 1, tr, max(ql, tm + 1), qr);
    }

    // Очистка памяти (важно для промышленного кода)
    ~Node() {
        delete l;
        delete r;
    }
};
