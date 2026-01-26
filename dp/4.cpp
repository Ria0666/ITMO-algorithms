#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct StateTable {
    int masks = 0;
    int block = 0;
    vector<long long> data;

    StateTable(int cols, int maskCount) : masks(maskCount), block(maskCount * maskCount) {
        data.assign(cols * block, 0LL);
    }

    long long& at(int col, int a, int b) {
        return data[col * block + a * masks + b];
    }

    long long at(int col, int a, int b) const {
        return data[col * block + a * masks + b];
    }

    long long* colPtr(int col) {
        return data.data() + col * block;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols;
    cin >> rows >> cols;

    if ((rows * cols) % 3 != 0) {
        cout << 0 << '\n';
        return 0;
    }

    if (rows > cols) swap(rows, cols);

    int maskCount = 1 << rows;
    StateTable dp(cols + 1, maskCount);
    dp.at(0, 0, 0) = 1;

    auto stepColumn = [&](int curMask, int nextInit, long long ways, long long* nextColumn) {
        auto dfs = [&](auto&& self, int pos, int cur, int add1, int add2) -> void {
            if (pos == rows) {
                int a = nextInit | add1;
                int b = add2;
                nextColumn[a * maskCount + b] += ways;
                return;
            }

            if (cur & (1 << pos)) {
                self(self, pos + 1, cur, add1, add2);
                return;
            }

            if (pos + 2 < rows) {
                int bit1 = 1 << (pos + 1);
                int bit2 = 1 << (pos + 2);
                if ((cur & bit1) == 0 && (cur & bit2) == 0) {
                    int filled = cur | (1 << pos) | bit1 | bit2;
                    self(self, pos + 3, filled, add1, add2);
                }
            }

            int bit = 1 << pos;
            if (((nextInit | add1 | add2) & bit) == 0) {
                self(self, pos + 1, cur | bit, add1 | bit, add2 | bit);
            }
        };

        dfs(dfs, 0, curMask, 0, 0);
    };

    for (int col = 0; col < cols; ++col) {
        long long* nextColumn = dp.colPtr(col + 1);

        for (int a = 0; a < maskCount; ++a) {
            for (int b = 0; b < maskCount; ++b) {
                long long ways = dp.at(col, a, b);
                if (!ways) continue;
                stepColumn(a, b, ways, nextColumn);
            }
        }
    }

    cout << dp.at(cols, 0, 0) << '\n';
    return 0;
}
