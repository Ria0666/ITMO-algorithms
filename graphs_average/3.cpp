#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
    vector<vector<pair<unsigned long long, unsigned long long>>> adj;
    unsigned long long V;

public:
    Graph(unsigned long long V) : V(V) {
        adj.resize(V);
    }

    void add(unsigned long long start, unsigned long long end, unsigned long long weight) {
        adj[start - 1].push_back(make_pair(end - 1, weight));
        adj[end - 1].push_back(make_pair(start - 1, weight));
    }

    unsigned long long primMST() {
        priority_queue<pair<unsigned long long, unsigned long long>, vector<pair<unsigned long long, unsigned long long>>, greater<pair<unsigned long long, unsigned long long>>> pq;
        unsigned long long src = 0;

        vector<unsigned long long> key(V, INT_MAX);
        vector<unsigned long long> parent(V, -1);
        vector<bool> inMST(V, false);

        pq.push(make_pair(0, src));
        key[src] = 0;
        unsigned long long count = 0;

        while (!pq.empty()) {
            unsigned long long u = pq.top().second;
            pq.pop();

            if (!inMST[u]) {
                count += key[u];
                inMST[u] = true;
            }

            for (auto &p: adj[u]) {
                unsigned long long v = p.first;
                unsigned long long weight = p.second;

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
    unsigned long long n, m;
    cin >> n >> m;
    Graph g(n);

    for (unsigned long long i = 0; i < m; ++i) {
        unsigned long long start, end, weight;
        cin >> start >> end >> weight;
        g.add(start, end, weight);
    }

    cout<<g.primMST();
}

