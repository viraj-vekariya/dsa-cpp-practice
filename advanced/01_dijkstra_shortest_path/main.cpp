#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <cassert>
using namespace std;

struct Edge {
    int to;
    int weight;
};

// small road-network simulation: cities connected by roads with distances (km)
vector<int> dijkstra(vector<vector<Edge>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;

    // min-heap of (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (d > dist[node]) continue; // stale entry, a shorter path was already found

        for (const Edge& e : graph[node]) {
            int newDist = d + e.weight;
            if (newDist < dist[e.to]) {
                dist[e.to] = newDist;
                pq.push({newDist, e.to});
            }
        }
    }
    return dist;
}

int main() {
    vector<string> cityNames = {"A-town", "Brookfield", "Centerville", "Denton", "Eastwick", "Fairview"};
    int n = cityNames.size();
    vector<vector<Edge>> graph(n);

    auto addRoad = [&](int u, int v, int dist) {
        graph[u].push_back({v, dist});
        graph[v].push_back({u, dist});
    };

    // 0=A-town 1=Brookfield 2=Centerville 3=Denton 4=Eastwick 5=Fairview
    addRoad(0, 1, 7);
    addRoad(0, 2, 9);
    addRoad(0, 5, 14);
    addRoad(1, 2, 10);
    addRoad(1, 3, 15);
    addRoad(2, 3, 11);
    addRoad(2, 5, 2);
    addRoad(3, 4, 6);
    addRoad(5, 4, 9);

    cout << "Road network (city, roads):" << endl;
    for (int i = 0; i < n; i++) {
        cout << cityNames[i] << " -> ";
        for (const Edge& e : graph[i]) {
            cout << cityNames[e.to] << "(" << e.weight << "km) ";
        }
        cout << endl;
    }

    int source = 0;
    vector<int> dist = dijkstra(graph, source);

    cout << "\nShortest distances from " << cityNames[source] << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << cityNames[source] << " -> " << cityNames[i] << " : " << dist[i] << " km" << endl;
    }

    assert(dist[0] == 0);
    assert(dist[1] == 7);
    assert(dist[2] == 9);
    assert(dist[5] == 11);
    assert(dist[4] == 20);
    assert(dist[3] == 20);

    cout << "\nAll checks passed." << endl;
    return 0;
}
