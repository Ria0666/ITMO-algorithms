#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double capacity;
    cin >> n >> capacity;

    vector<double> w(n);
    vector<int> val(n);

    int totalVal = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> val[i];
        totalVal += val[i];
    }

    double big = numeric_limits<double>::infinity();
    vector<double> bestWeight(totalVal + 1, big);
    bestWeight[0] = 0.0;

    for (int i = 0; i < n; ++i) {
        int add = val[i];
        double wt = w[i];
        for (int v = totalVal; v >= add; --v) {
            double cand = bestWeight[v - add] + wt;
            if (cand < bestWeight[v]) bestWeight[v] = cand;
        }
    }

    int ans = 0;
    for (int v = totalVal; v >= 0; --v) {
        if (bestWeight[v] <= capacity + 1e-9) {
            ans = v;
            break;
        }
    }

    cout << ans << '\n';
    return 0;
}
