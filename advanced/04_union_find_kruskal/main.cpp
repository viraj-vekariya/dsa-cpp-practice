#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

class UnionFind {
    vector<int> parent;
    vector<int> rank_;
public:
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // path compression: flatten the tree on the way up so future finds are near O(1)
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) return false;

        // union by rank: attach the shorter tree under the taller one
        if (rank_[rootA] < rank_[rootB]) {
            parent[rootA] = rootB;
        } else if (rank_[rootA] > rank_[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rank_[rootA]++;
        }
        return true;
    }
};

struct WeightedEdge {
    int u, v, weight;
};

int main() {
    int numNodes = 6;
    vector<WeightedEdge> edges = {
        {0, 1, 4},
        {0, 2, 4},
        {1, 2, 2},
        {1, 0, 4},
        {2, 3, 3},
        {2, 5, 2},
        {2, 4, 4},
        {3, 4, 3},
        {5, 4, 3}
    };

    cout << "Graph edges (u, v, weight):" << endl;
    for (const WeightedEdge& e : edges) {
        cout << "(" << e.u << ", " << e.v << ", " << e.weight << ")" << endl;
    }

    sort(edges.begin(), edges.end(), [](const WeightedEdge& a, const WeightedEdge& b) {
        return a.weight < b.weight;
    });

    UnionFind uf(numNodes);
    vector<WeightedEdge> mst;
    int totalWeight = 0;

    for (const WeightedEdge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
        }
    }

    cout << "\nMinimum spanning tree edges:" << endl;
    for (const WeightedEdge& e : mst) {
        cout << e.u << " -- " << e.v << " (weight " << e.weight << ")" << endl;
    }
    cout << "\nTotal MST weight: " << totalWeight << endl;

    assert((int)mst.size() == numNodes - 1);
    assert(totalWeight == 14);

    cout << "\nAll checks passed." << endl;
    return 0;
}
