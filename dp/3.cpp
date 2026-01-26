#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int weight;
    double value;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;
    cin >> n >> capacity;

    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        cin >> items[i].weight >> items[i].value;
    }

    int cols = capacity + 1;
    vector<double> leftDp((n + 1) * cols, 0.0);
    vector<double> rightDp((n + 1) * cols, 0.0);

    auto L = [&](int i, int c) -> double& { return leftDp[i * cols + c]; };
    auto R = [&](int i, int c) -> double& { return rightDp[i * cols + c]; };

    for (int i = 0; i < n; ++i) {
        int w = items[i].weight;
        double v = items[i].value;

        for (int c = 0; c <= capacity; ++c) {
            double best = L(i, c);
            if (c >= w) best = max(best, L(i, c - w) + v);
            L(i + 1, c) = best;
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        int w = items[i].weight;
        double v = items[i].value;

        for (int c = 0; c <= capacity; ++c) {
            double best = R(i + 1, c);
            if (c >= w) best = max(best, R(i + 1, c - w) + v);
            R(i, c) = best;
        }
    }

    cout << fixed << setprecision(9);

    for (int banned = 0; banned < n; ++banned) {
        double best = 0.0;
        for (int c = 0; c <= capacity; ++c) {
            best = max(best, L(banned, c) + R(banned + 1, capacity - c));
        }
        cout << best << '\n';
    }

    return 0;
}
