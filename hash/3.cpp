#include <iostream>
#include <vector>
using namespace std;

int calculate_hash(int value, int count) {
    return (value + 1000000) % (3 * count);
}

int comb2(int n) {
    if (n < 2) return 0;
    return n * (n - 1) / 2;
}

int main() {
    int num_chairs;
    cin >> num_chairs;
    vector<int> heights(num_chairs);

    for (int i = 0; i < num_chairs; i++) {
        cin >> heights[i];
    }

    vector<vector<int>> hash_table(3 * num_chairs);

    for (int i = 0; i < num_chairs; i++) {
        int hash_key = calculate_hash(heights[i] - i, num_chairs);
        hash_table[hash_key].push_back(heights[i]);
    }

    int total_pairs = 0;
    for (auto& bucket : hash_table) {
        int bucket_size = bucket.size();
        total_pairs += comb2(bucket_size);
    }

    cout << total_pairs << endl;
}

