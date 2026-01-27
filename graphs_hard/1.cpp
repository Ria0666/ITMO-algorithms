#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    vector<int> current;
    vector<vector<int>> graph;
    vector<bool> visited;

    Graph(int n, int m) : graph(n * m), current(n * m, -1), visited(n * m, false) {}

    int node(int i, int j, int m) {
        return i * m + j;
    }

    bool kuhn(int v) {
        if (visited[v]) return false;
        visited[v] = true;
        for (int to : graph[v]) {
            if (current[to] == -1 || kuhn(current[to])) {
                current[to] = v;
                return true;
            }
        }
        return false;
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    Graph g(n, m);

    vector<vector<bool>> adj(n, vector<bool>(m, true));
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        adj[x-1][y-1] = false;
    }

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (adj[x][y]) {
                if ((x + y) % 2 == 0) {
                    if (x + 1 < n && adj[x + 1][y])
                        g.graph[g.node(x, y, m)].push_back(g.node(x + 1, y, m));
                    if (y + 1 < m && adj[x][y + 1]) 
                        g.graph[g.node(x, y, m)].push_back(g.node(x, y + 1, m));
                    if (x - 1 >= 0 && adj[x - 1][y])
                        g.graph[g.node(x, y, m)].push_back(g.node(x - 1, y, m));
                    if (y - 1 >= 0 && adj[x][y - 1]) 
                        g.graph[g.node(x, y, m)].push_back(g.node(x, y - 1, m));
                }
            }
        }
    }
    
    int count = 0;
    for (int v = 0; v < n * m; ++v) {
        if ((v / m + v % m) % 2 == 0 && g.current[v] == -1) {
            fill(g.visited.begin(), g.visited.end(), false);
            if (g.kuhn(v)) count++;
        }
    }

    cout << count * 2;
}

