#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
    vector<vector<pair<long long, long long>>> adj;
    long long V;

public:
    Graph(long long V) : V(V) {
        adj.resize(V);
    }

    void add(long long start, long long end, long long weight) {
        adj[start - 1].push_back(make_pair(end - 1, weight));
        adj[end - 1].push_back(make_pair(start - 1, weight));
    }

    int primMST() {
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
        long long src = 0;

        vector<long long> key(V, INT_MAX);
        vector<long long> parent(V, -1);
        vector<bool> inMST(V, false);

        pq.push(make_pair(0, src));
        key[src] = 0;
        long long count = 0;

        while (!pq.empty()) {
            long long u = pq.top().second;
            pq.pop();

            if (!inMST[u]) {
                count += key[u];
                inMST[u] = true;
            }

            for (auto &p: adj[u]) {
                long long v = p.first;
                long long weight = p.second;

                if (!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }
        return count;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m;
    cin >> n >> m;
    Graph g(n);

    for (long long i = 0; i < m; ++i) {
        long long start, end, weight;
        cin >> start >> end >> weight;
        g.add(start, end, weight);
    }

    cout<<g.primMST();
}

