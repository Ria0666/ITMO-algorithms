#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class SMN {
public:
    vector<int> parent, rank;

    SMN(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int get(int v) {
        if (v == parent[v]) return v;
        return parent[v] = get(parent[v]);
    }

    void merge(int a, int b) {
        a = get(a), b = get(b);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
};

int main() {
    int n, m;
    long long q;
    cin >> n >> m >> q;
    vector<pair<int, int>> edges(m), question(q);
    vector<bool> isRemoval(q), answers;
    set<pair<int, int>> removals;

    for (int i = 0; i < m; i++) {
        int start, end;
        cin >> start >> end;
        if (start>end) swap(start,end);
        edges[i].first=start;
        edges[i].second=end;
    }

    for (long long i = 0; i < q; ++i) {
        char znak;
        int first, second;
        cin >> znak >> first >> second;
        if (first>second) swap(first,second);
        question[i].first=first;
        question[i].second=second;
        isRemoval[i] = (znak == '-');
        if (isRemoval[i]) {
            removals.insert(question[i]);
        }
    }

    SMN smn(n + 1);
    for (auto edge : edges) {
        if (removals.find(edge) == removals.end()) {
            smn.merge(edge.first, edge.second);
        }
    }

    for (int i = q - 1; i >= 0; --i) {
        if (isRemoval[i]) {
            smn.merge(question[i].first, question[i].second);
        }
        else
            answers.push_back(smn.get(question[i].first) == smn.get(question[i].second));
    }

    reverse(answers.begin(), answers.end());
    for (bool answer : answers) {
        if (answer) cout<<"YES"<<"\n";
        else cout<<"NO"<<"\n";
    }
}

