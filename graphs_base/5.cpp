#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

class Graph {
    vector<vector<int>> dist;

public:
    Graph(int n) : dist(n, vector<int>(n, INF)) {
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
    }

    void add(int start, int end, int weight) {
        dist[start - 1][end - 1] = min(dist[start - 1][end - 1], weight);
    }

    vector<vector<int>> floid() {
        int n = dist.size();
        for (int v = 0; v < n; v++) {
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    if (dist[a][v] < INF && dist[v][b] < INF)
                        dist[a][b] = max(dist[a][v] + dist[v][b], -INF);
                }
            }
        }
        return dist;
    }
};

int main() {
    int N, k;
    cin >> N >> k;

    for (int i = 0; i < N; i++) {
        int n, m;
        cin >> n >> m;
        Graph g(n);
        for (int t = 0; t < m; t++) {
            int start, end, weight;
            cin >> start >> end >> weight;
            g.add(start, end, weight);
        }
        vector<vector<int>> res = g.floid();
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (res[j][j] < 0) count++;
        }
        if (count < k || !count) cout << "YES"<<endl;
        else cout << "NO"<<endl;
    }
    cout << endl;
}

