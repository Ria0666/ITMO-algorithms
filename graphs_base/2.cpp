#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int INF = 1e9;

class Graph {
public:
    vector<vector<pair<int,int>>> graph;

    Graph (int n) {
        graph.resize(n);
    }

    void addEdge (int start,int end, int weight) {
        graph[start].push_back({end,weight});
    }

    vector<int> deicstr (int start) {
        vector<int> dist(graph.size(),INF);
        dist[start]=0;
        set<pair<int,int>> q;
        q.insert({dist[start],start});
        while (!q.empty()) {
            int near=q.begin()->second;
            q.erase(q.begin());
            for (auto &[to,weight]: graph[near]) {
                if (dist[to]>dist[near]+weight) {
                    q.erase ({dist[to],to});
                    dist[to]=dist[near]+weight;
                    q.insert({dist[to],to});
                }
            }
        }
        return dist;
    }
};
int main() {
    int n,m;
    cin>>n>>m;
    Graph g(n);
    for (int i =0 ; i < m; i++) {
        int start,end,weight;
        cin>>start>>end>>weight;
        g.addEdge(start-1,end-1,weight);
    }
    vector<int> res = g.deicstr(0);
    if (res[n-1]!=INF) cout<<res[n-1];
    else cout<<"-1";

}
