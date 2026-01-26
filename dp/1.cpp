#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long  n, m;
    cin >> n >> m;
    vector<vector<long long>> field(n, vector<long long>(m));
    vector<vector<long long>> masha(n, vector<long long>(m, 0));
    vector<vector<long long>> dasha(n, vector<long long>(m, 0));
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < m; ++j) {
            cin >> field[i][j];
        }
    }
    masha[0][0] = field[0][0];
    for (long long i = 1; i < n; ++i) masha[i][0] = masha[i - 1][0] + field[i][0];
    for (long long j = 1; j < m; ++j) masha[0][j] = masha[0][j - 1] + field[0][j];
    for (long long i = 1; i < n; ++i) {
        for (long long j = 1; j < m; ++j) {
            masha[i][j] = max(masha[i - 1][j], masha[i][j - 1]) + field[i][j];
        }
    }
    dasha[n - 1][m - 1] = field[n - 1][m - 1];
    for (long long i = n - 2; i >= 0; --i) dasha[i][m - 1] = dasha[i + 1][m - 1] + field[i][m - 1];
    for (long long j = m - 2; j >= 0; --j) dasha[n - 1][j] = dasha[n - 1][j + 1] + field[n - 1][j];
    for (long long i = n - 2; i >= 0; --i) {
        for (long long j = m - 2; j >= 0; --j) {
            dasha[i][j] = max(dasha[i + 1][j], dasha[i][j + 1]) + field[i][j];
        }
    }
    long long q;
    cin >> q;
    while (q--) {
        long long x, y;
        cin >> x >> y;
        cout << masha[x][y] + dasha[x][y] - field[x][y] << endl;
    }
}
