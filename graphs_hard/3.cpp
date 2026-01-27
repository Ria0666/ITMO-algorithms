#include "blazingio.hpp"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

class UF {
public:
    vector<int> p;

    UF(int n) : p(n) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int i) {
        if (p[i] != i) {
            p[i] = find(p[i]);
        }
        return p[i];
    }

    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            p[ry] = rx;
        }
    }
};

class Net {
public:
    int v;
    vector<pair<int, pair<int, int>>> con;

    Net(int v) : v(v) {}

    void add(int u, int v, int w) {
        con.emplace_back(w, make_pair(u, v));
    }
};

bool edgeCompare(pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
    return a.first < b.first;
}

void mst(Net& net, vector<unordered_map<int, int>>& t) {
    UF uf(net.v);
    sort(net.con.begin(), net.con.end(), edgeCompare);

    for (auto& c : net.con) {
        int w = c.first;
        int u = c.second.first;
        int v = c.second.second;

        if (uf.find(u) != uf.find(v)) {
            t[u][v] = w;
            t[v][u] = w;
            uf.unite(u, v);
        }
    }
}

void dfs(int cur, vector<int>& p, vector<int>& s, vector<int>& o, vector<unordered_map<int, int>>& t, vector<bool>& seen) {
    seen[cur] = true;
    for (auto& n : t[cur]) {
        int ne = n.first;
        int w = n.second;
        if (!seen[ne]) {
            dfs(ne, p, s, o, t, seen);
            p[cur] = max(p[cur], s[ne] + w - o[ne]);
            s[cur] += o[ne];
        }
    }
    p[cur] += s[cur];
    o[cur] = max(p[cur], s[cur]);
}

int main() {
    int n, e;
    cin >> n >> e;
    vector<int> d1(n), d2(n), d3(n);
    vector<bool> v(n, false);
    vector<unordered_map<int, int>> tree(n);
    Net net(n);

    for (int i = 0; i < e; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        net.add(a - 1, b - 1, l);
    }

    mst(net, tree);
    dfs(0, d1, d2, d3, tree, v);
    cout << d3[0];
}

