#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int INF = 1e9;

bool bfs(int a, vector<vector<int>> &graph, set<pair<int, int>> &removed, int check) {

    vector<int> dist(graph.size(), INF);
    queue<int> q;
    dist[a] = 0;
    q.push(a);

    while (!q.empty()) {
        if (dist[check]!=INF) return true;
        int temp = q.front();
        q.pop();
        for (int to : graph[temp]) {
            if (dist[to] == INF && removed.find({temp, to}) == removed.end()) {
                dist[to] = dist[temp] + 1;
                q.push(to);
            }
        }
    }

    return dist[check] != INF;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> graph(n);
    set<pair<int, int>> removed;

    for (int i = 0; i < m; i++) {
        int start, end;
        cin >> start >> end;
        graph[start-1].push_back(end-1);
        graph[end-1].push_back(start-1);
    }

    for (int i = 0; i < q; i++) {
        char znak;
        int first, second;
        cin >> znak >> first >> second;

        if (znak == '?') {
            if (bfs(first-1, graph, removed, second-1)) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        if (znak == '-') {
            removed.insert({first-1, second-1});
            removed.insert({second-1, first-1});
        }
    }
}

