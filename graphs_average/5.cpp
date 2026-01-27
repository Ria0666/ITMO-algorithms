#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:
    vector<vector<int>> graph;
    stack<int> s;
    vector<int> t_in, up;
    vector<bool> visited;
    int maxColor, timer;
public:
    vector<int> colors;

    Graph(int n) : graph(n), colors(n, 0), t_in(n, -1), up(n, 0), visited(n, false), maxColor(0), timer(0) {}

    void paint(int v) {
        maxColor++;
        int last = -1;
        while (last != v && !s.empty()) {
            colors[s.top()] = maxColor;
            last = s.top();
            s.pop();
        }
    }

    void dfs(int v, int p = -1) {
        s.push(v);
        visited[v] = true;
        t_in[v] = up[v] = timer++;
        for (int u : graph[v]) {
            if (u == p) continue;
            if (visited[u])
                up[v] = min(up[v], t_in[u]);
            else {
                dfs(u, v);
                up[v] = min(up[v], up[u]);
                if (up[u] > t_in[v])
                    paint(u);
            }
        }
        if (p == -1)
            paint(v);
    }

    void addEdge(int start, int end) {
        graph[start].push_back(end);
        graph[end].push_back(start);
    }

    void find() {
        for (int i = 0; i < graph.size(); i++) {
            if (!visited[i]) dfs(i);
        }
    }

};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    Graph g(n+1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }

    g.find();

    for (int i = 0; i < q; ++i) {
        int first,second;
        cin>>first>>second;
        if (g.colors[first]==g.colors[second]) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}

