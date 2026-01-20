#include <iostream>
#include <utility>

using namespace std;

constexpr int MAX_BLOCKS = 30000;
constexpr int MAX_EVENTS = 80000;
constexpr int LEASE = 600;

struct MinHeapInt {
    int a[MAX_BLOCKS + 5]{};
    int n = 0;

    bool empty() const { return n == 0; }

    void push(int x) {
        int i = ++n;
        while (i > 1) {
            int p = i / 2;
            if (a[p] <= x) break;
            a[i] = a[p];
            i = p;
        }
        a[i] = x;
    }

    int pop() {
        int res = a[1];
        int x = a[n--];

        int i = 1;
        while (true) {
            int l = i * 2;
            if (l > n) break;
            int r = l + 1;
            int c = (r <= n && a[r] < a[l]) ? r : l;
            if (a[c] >= x) break;
            a[i] = a[c];
            i = c;
        }
        a[i] = x;
        return res;
    }

    void heapifyFromArray(int* src, int cnt) {
        n = cnt;
        for (int i = 1; i <= n; ++i) a[i] = src[i];
        for (int i = n / 2; i >= 1; --i) {
            int x = a[i];
            int v = i;
            while (true) {
                int l = v * 2;
                if (l > n) break;
                int r = l + 1;
                int c = (r <= n && a[r] < a[l]) ? r : l;
                if (a[c] >= x) break;
                a[v] = a[c];
                v = c;
            }
            a[v] = x;
        }
    }
};

struct MinHeapEvent {
    int t[MAX_EVENTS + 5]{};
    int b[MAX_EVENTS + 5]{};
    int n = 0;

    bool empty() const { return n == 0; }
    int topTime() const { return t[1]; }

    void push(int time, int block) {
        int i = ++n;
        t[i] = time;
        b[i] = block;

        while (i > 1) {
            int p = i / 2;
            if (t[p] <= t[i]) break;
            swap(t[p], t[i]);
            swap(b[p], b[i]);
            i = p;
        }
    }

    void pop(int& time, int& block) {
        time = t[1];
        block = b[1];

        int xt = t[n];
        int xb = b[n];
        --n;

        int i = 1;
        while (true) {
            int l = i * 2;
            if (l > n) break;
            int r = l + 1;
            int c = (r <= n && t[r] < t[l]) ? r : l;
            if (t[c] >= xt) break;
            t[i] = t[c];
            b[i] = b[c];
            i = c;
        }
        t[i] = xt;
        b[i] = xb;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MinHeapInt freeBlocks;
    MinHeapEvent exp;

    static int tmp[MAX_BLOCKS + 5];
    for (int i = 1; i <= MAX_BLOCKS; ++i) tmp[i] = i;
    freeBlocks.heapifyFromArray(tmp, MAX_BLOCKS);

    static int release[MAX_BLOCKS + 1]{};

    auto freeExpired = [&](int now) {
        while (!exp.empty() && exp.topTime() <= now) {
            int t, b;
            exp.pop(t, b);
            if (release[b] == t) {
                release[b] = 0;
                freeBlocks.push(b);
            }
        }
    };

    int time;
    char op;
    while (cin >> time >> op) {
        freeExpired(time);

        if (op == '+') {
            if (freeBlocks.empty()) {
                cout << "-\n";
                continue;
            }
            int b = freeBlocks.pop();
            int until = time + LEASE;
            release[b] = until;
            exp.push(until, b);
            cout << b << "\n";
        } else if (op == '.') {
            int b;
            cin >> b;
            if (b >= 1 && b <= MAX_BLOCKS && release[b] > time) {
                int until = time + LEASE;
                release[b] = until;
                exp.push(until, b);
                cout << "+\n";
            } else {
                cout << "-\n";
            }
        }
    }
    return 0;
}
