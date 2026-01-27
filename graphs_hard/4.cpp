#include "blazingio.hpp"
#include <vector>
#include <queue>
using namespace std;

class Graph {
public:
    vector<int> current;       
    vector<int> pairs;
    vector<vector<int>> owners;
    vector<vector<int>> kittens;
    queue<int> freeKittens;

    Graph(int n, vector<vector<int>>& kittensPr, vector<vector<int>>& ownersPr)
            : current(n, -1), pairs(n, -1), owners(n, vector<int>(n)), kittens(kittensPr) {

        for (int i = 0; i < n; i++) {
            for (int rank = 0; rank < n; rank++) {
                owners[i][ownersPr[i][rank]] = rank;
            }
        }

        for (int i = 0; i < n; i++) {
            freeKittens.push(i);
        }
    }

    vector<int> match(int n) {
        while (!freeKittens.empty()) {
            int w = freeKittens.front();
            freeKittens.pop();
            for (int rank = 0; rank < n; ++rank) {
                int m = kittens[w][rank];
                int currentPartner = current[m];
                if (currentPartner == -1) {
                    current[m] = w;
                    pairs[w] = m;
                    break;
                } else if (owners[m][w] < owners[m][currentPartner]) {
                    current[m] = w;
                    pairs[w] = m;
                    pairs[currentPartner] = -1;
                    freeKittens.push(currentPartner);
                    break;
                }
            }
        }
        return pairs;
    }
};

int main() {
    int n;
    cin >> n;

    vector<vector<int>> kittens(n, vector<int>(n));
    vector<vector<int>> owners(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> kittens[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> owners[i][j];
        }
    }

    Graph g(n, kittens, owners);
    vector<int> result = g.match(n);

    for (int w = 0; w < n; ++w) {
        if (result[w] != -1)
            cout << w << " " << result[w] << endl;
    }
}

