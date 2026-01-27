#include <iostream>
#include <vector>

using namespace std;

const unsigned long long INF = 18446744073709551615ULL;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<unsigned long long>> dist(n, vector<unsigned long long>(n, INF));

    for (int i = 0; i < m; i++) {
        int start, end;
        unsigned long long weight;
        cin >> start >> end >> weight;
        dist[start-1][end-1] = min(dist[start-1][end-1], weight);
        dist[end-1][start-1] = min(dist[end-1][start-1], weight);
    }

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int v = 0; v < n; v++) {
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
                if (dist[a][v] < INF && dist[v][b] < INF)
                    dist[a][b]=min(dist[a][b],dist[a][v]+dist[v][b]);
            }
        }
    }

    unsigned long long maxx = INF;
    unsigned long long bestHouse = -1;
    for (int i = 0; i < n; i++) {
        unsigned long long sum = 0;
        for (int j = 0; j < n; j++) {
            sum += dist[i][j];
        }
        if (sum < maxx) {
            maxx = sum;
            bestHouse = i;
        }
    }
    cout << bestHouse + 1 << endl;
}

