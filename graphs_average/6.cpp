#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to, weight;
};

class Graph {
    vector<vector<Edge>> graph;
    int n;
public:
    vector<int> distances;

    Graph(int n) : n(n), graph(n + 1), distances(n + 1, INT_MAX) {}

    void addEdge(int from, int to, int weight) {
        graph[from].push_back({to, weight});
        graph[to].push_back({from, weight});
    }

    void shortest(int source) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, source});
        distances[source] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& edge : graph[u]) {
                int v = edge.to;
                int weight = edge.weight;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    pq.push({distances[v], v});
                }
            }
        }
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int s, t;
        cin >> s >> t;
        vector<int> islands(s);
        for (int j = 0; j < s; j++) {
            cin >> islands[j];
        }

        for (int j = 0; j < s; j++) {
            for (int l = j + 1; l < s; l++) {
                g.addEdge(islands[j], islands[l], t);
            }
        }
    }

    g.shortest(1);

    if (g.distances[k] != INT_MAX) {
        cout << g.distances[k];
    } else {
        cout << -1;
    }
}

