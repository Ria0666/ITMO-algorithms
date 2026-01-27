#include <iostream>
#include <vector>
using namespace std;

long long hash_function(long long x) {
    return x % 1000007;
}

int main() {
    int n;
    cin >> n;

    vector<int> degrees1(n, 0);
    vector<int> degrees2(n, 0);
    vector<long long> hash_table1(1000007, 0);
    vector<long long> hash_table2(1000007, 0);

    int u, v;

    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        degrees1[u - 1]++;
        degrees1[v - 1]++;
    }

    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        degrees2[u - 1]++;
        degrees2[v - 1]++;
    }

    for (int degree : degrees1) {
        ++hash_table1[hash_function(degree)];
    }

    for (int degree : degrees2) {
        ++hash_table2[hash_function(degree)];
    }

    bool are_equal = true;
    for (int i = 0; i < 1000007; i++) {
        if (hash_table1[i] != hash_table2[i]) {
            are_equal = false;
            break;
        }
    }

    if (are_equal)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

