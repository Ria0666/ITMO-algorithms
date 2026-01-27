#include <iostream>
#include <vector>
using namespace std;

struct Rib {
    int to, capacity, cost, flow;
    size_t back;
};

class Graph {
public:
    vector<vector<Rib>> adj;
    int n;

    Graph(int n) : n(n), adj(n) {}

    void addEdge(int from, int to, int capacity, int cost) {
        Rib forward = {to, capacity, cost, 0, adj[to].size()};
        Rib backward = {from, 0, -cost, 0, adj[from].size()};
        adj[from].push_back(forward);
        adj[to].push_back(backward);
    }

    pair<int, int> minCost(int s, int t) {
        int flow = 0, cost = 0;
        vector<int> id(n, 0);
        vector<int> d(n);
        vector<int> q(n);
        vector<int> p(n);
        vector<size_t> p_rib(n);

        while (true) {
            fill(d.begin(), d.end(), INT_MAX);
            d[s] = 0;
            int qh = 0, qt = 0;
            q[qt++] = s;
            id[s] = 1;

            while (qh != qt) {
                int v = q[qh++];
                id[v] = 0;
                if (qh == n) qh = 0;

                for (size_t i = 0; i < adj[v].size(); ++i) {
                    Rib &r = adj[v][i];
                    if (r.flow < r.capacity && d[v] + r.cost < d[r.to]) {
                        d[r.to] = d[v] + r.cost;
                        if (id[r.to] == 0) {
                            q[qt++] = r.to;
                            if (qt == n) qt = 0;
                            id[r.to] = 1;
                        }
                        p[r.to] = v;
                        p_rib[r.to] = i;
                    }
                }
            }

            if (d[t] == INT_MAX) break;
            int addFlow = INT_MAX;

            for (int v = t; v != s; v = p[v]) {
                int pv = p[v];
                size_t pr = p_rib[v];
                addFlow = min(addFlow, adj[pv][pr].capacity - adj[pv][pr].flow);
            }
            for (int v = t; v != s; v = p[v]) {
                int pv = p[v];
                size_t pr = p_rib[v];
                Rib &r = adj[pv][pr];
                r.flow += addFlow;
                adj[r.to][r.back].flow -= addFlow;
                cost += r.cost * addFlow;
            }
            flow += addFlow;
        }
        return {flow, cost};
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c, p;
        cin >> u >> v >> c >> p;
        g.addEdge(u-1, v-1, c, p);
    }

    auto result = g.minCost(s-1, t-1);
    cout << result.first << " " << result.second;
}

