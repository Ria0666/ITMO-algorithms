#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Query {
    int i, j, k;
};

int main() {
    int N, M;
    cin >> N >> M;

    string song;
    cin >> song;

    vector<Query> queries(M);
    for (int q = 0; q < M; q++) {
        int i, j, k;
        std::cin >> i >> j >> k;
        queries[q] = {i - 1, j - 1, k};
    }

    int count = 0;
    for (auto &query: queries) {
        int i = query.i;
        int j = query.j;
        int k = query.k;

        if (song.substr(i, k) == song.substr(j, k))
            count++;
    }

    cout << count << endl;
}

