#include "blazingio.hpp"
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
public:
    vector<vector<int>> capacity;
    vector<vector<int>> adj;

    Graph(int n) : capacity(n, vector<int>(n, 0)), adj(n) {}

    void add_edge(int from, int to, int cap) {
        adj[from - 1].push_back(to - 1); 
        adj[to - 1].push_back(from - 1); 
        capacity[from - 1][to - 1] = cap; 
    }

    int bfs(int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});
        parent[s] = -2;

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    }

    int maxflow(int s, int t) {
        int total_flow = 0;
        vector<int> parent(adj.size());
        int flow;

        while (flow = bfs(s, t, parent)) {
            total_flow += flow;
            int cur = t;
            while (cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= flow;
                capacity[cur][prev] += flow;
                cur = prev;
            }
        }
        return total_flow;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++) {
        int from, to, cap;
        cin >> from >> to >> cap;
        g.add_edge(from, to, cap);
    }

    cout << g.maxflow(0, n-1);
}

