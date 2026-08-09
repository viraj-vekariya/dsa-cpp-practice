#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;
public:
    Graph(int numNodes) : n(numNodes), adj(numNodes) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> bfs(int start) {
        vector<bool> visited(n, false);
        vector<int> order;
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);
            for (int next : adj[node]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        return order;
    }

    void dfsHelper(int node, vector<bool>& visited, vector<int>& order) {
        visited[node] = true;
        order.push_back(node);
        for (int next : adj[node]) {
            if (!visited[next]) dfsHelper(next, visited, order);
        }
    }

    vector<int> dfs(int start) {
        vector<bool> visited(n, false);
        vector<int> order;
        dfsHelper(start, visited, order);
        return order;
    }

    vector<vector<int>> connectedComponents() {
        vector<bool> visited(n, false);
        vector<vector<int>> components;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                vector<int> comp;
                dfsHelper(i, visited, comp);
                components.push_back(comp);
            }
        }
        return components;
    }
};

void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "]";
}

int main() {
    // graph: 0-1-2-3 form one component, 4-5 another, 6 is isolated
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(0, 3);
    g.addEdge(4, 5);

    cout << "BFS from 0: ";
    vector<int> bfsOrder = g.bfs(0);
    printVec(bfsOrder);
    cout << endl;
    assert(bfsOrder.size() == 4);
    assert(bfsOrder[0] == 0);

    cout << "DFS from 0: ";
    vector<int> dfsOrder = g.dfs(0);
    printVec(dfsOrder);
    cout << endl;
    assert(dfsOrder.size() == 4);
    assert(dfsOrder[0] == 0);

    cout << "\nConnected components:" << endl;
    vector<vector<int>> comps = g.connectedComponents();
    for (const auto& comp : comps) {
        printVec(comp);
        cout << endl;
    }
    assert(comps.size() == 3);

    cout << "\nAll checks passed." << endl;
    return 0;
}
