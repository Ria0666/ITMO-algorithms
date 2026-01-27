#include <iostream>
#include <vector>
#include <set>
#include <deque>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<set<int>> g(n);
    vector<bool> visited(n, false);
    deque<int> order;

    for (int i = 0; i < m; i++) {
        int start, end;
        cin >> start >> end;
        g[start].insert(end);
        g[end].insert(start);
        if (!visited[start]) {
            order.push_back(start);
            visited[start] = true;
        }
        if (!visited[end]) {
            order.push_back(end);
            visited[end] = true;
        }
    }
    
    for (int i = 0; i < n * (n - 1); ++i) {
        if (!g[order[0]].contains(order[1])) {
            int k = 2;
            while (k + 1 < order.size() &&
                   (!g[order[0]].contains(order[k]) || !g[order[k]].contains(order[1])))
                k++;
            if (k + 1 < order.size()) {
                reverse(order.begin() + 1, order.begin() + k + 1);
            }
        }
        order.push_back(order.front());
        order.pop_front();
    }
    
    for (int i = 0; i < n; ++i)
        cout << order[i] << " ";
}

