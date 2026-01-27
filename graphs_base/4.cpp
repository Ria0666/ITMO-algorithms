#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    vector<vector<int>> graph;
    vector <int> visited, order;
    vector<int> t_in, up;
    int timer = 0;

    void dfs(int v, int p = -1) {
        visited[v] = true;
        t_in[v] = up[v] = timer++;
        for (int to : graph[v]) {
            if (to == p) continue;
            if (!visited[to]) {
                dfs(to, v);
                up[v] = min(up[v], up[to]);
            } else
                up[v] = min(up[v], t_in[to]);
            if (up[to] > t_in[v]) {
                if (v < to) bridge.push_back({v, to});
                else bridge.push_back({to, v});
            }
        }
    }

public:
    vector<pair<int,int>> bridge;
    Graph (int n) {
        graph.resize(n);
    }

    void addEdge (int start,int end) {
        graph[start].push_back(end);
        graph[end].push_back(start);
    }

    vector<pair<int,int>> find_bridges(int n) {
        visited.assign(n, false);
        t_in.assign(n, -1);
        up.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
        sort(bridge.begin(), bridge.end());
        return bridge;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int start, end;
        cin >> start >> end;
        g.addEdge(start - 1, end - 1);
    }
    vector<pair<int, int>> bridges = g.find_bridges(n);
    for (int i = 0; i < bridges.size(); i++) {
        cout << bridges[i].first + 1 << " " << bridges[i].second + 1 << endl;
    }
}

