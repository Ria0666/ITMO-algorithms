#include "blazingio.hpp"
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<bool> visited;
vector<int> disc, low, parent;
set<int> articulationPoints;

void dfs(int u, bool isRoot, int time) {
    visited[u] = true;
    disc[u] = low[u] = time++;
    int children = 0;
    bool isArticulationPoint = false;
    for (int v : graph[u]) {
        if (!visited[v]) {
            children++;
            parent[v] = u;
            dfs(v, false,time++);
            low[u] = min(low[u], low[v]);
            if (!isRoot && low[v] >= disc[u])
                isArticulationPoint = true;
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
    if ((isRoot && children > 1) || (!isRoot && isArticulationPoint))
        articulationPoints.insert(u);
}

void dfsCount(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v] && articulationPoints.find(v) == articulationPoints.end())
            dfsCount(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n);
    visited.assign(n, false);
    disc.assign(n, 0);
    low.assign(n, 0);
    parent.assign(n, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i, true,0);
    }

    set<int> marked(articulationPoints);

    int components = 0;
    visited.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && marked.find(i) == marked.end()) {
            dfsCount(i);
            components++;
        }
    }

    cout << components;
}

