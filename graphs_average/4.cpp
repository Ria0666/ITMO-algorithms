#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    vector<vector<pair<unsigned long long, bool>>> adj;
    vector<unsigned long long> degree;
    vector<bool> visited;
    unsigned long long vertex;
public:
    Graph(unsigned long long n) : vertex(n), adj(n + 1), degree(n + 1, 0), visited(n + 1, false) {}

    void dfs(unsigned long long v, vector<unsigned long long>& path) {
        visited[v] = true;
        for (auto& edge : adj[v]) {
            if (!edge.second) {
                edge.second = true;
                for (auto& e : adj[edge.first]) {
                    if (e.first == v && !e.second) {
                        e.second = true;
                        break;
                    }
                }
                dfs(edge.first, path);
            }
        }
        path.push_back(v);
    }

    void addEdge(unsigned long long a, unsigned long long b) {
        adj[a].emplace_back(b, false);
        adj[b].emplace_back(a, false);
        degree[a]++;
        degree[b]++;
    }

    bool isEulerian() {
        for (unsigned long long i = 1; i <= vertex; i++) {
            if (degree[i] % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    vector<unsigned long long> find() {
        vector<unsigned long long> path;
        dfs(1, path);
        reverse(path.begin(), path.end());
        return path;
    }

    bool allVisited() {
        for (unsigned long long i = 1; i <= vertex; i++) {
            if (!visited[i] && !adj[i].empty()) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    unsigned long long vertex, edges;
    cin >> vertex >> edges;

    Graph g(vertex);

    for (unsigned long long i = 0; i < edges; i++) {
        unsigned long long a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }

    if (!g.isEulerian()) {
        cout << ":(" << "\n";
        return 0;
    }

    auto path = g.find();

    if (!g.allVisited()) {
        cout << ":(" << "\n";
        return 0;
    }

    for (auto v : path) {
        cout << v << " ";
    }

    cout << "\n";
}

