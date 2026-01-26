#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int binarySearch(vector<long long>& ends, int target) {
    int left = 0;
    int right = ends.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (ends[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n;
    cin >> n;
    vector<long long> heights(n);
    for (int i = 0; i < n; ++i) cin >> heights[i];
    vector<long long> nvp(n, 1);
    vector<long long> ends;
    for (int i = 0; i < n; ++i) {
        int current_height = heights[i];
        int index = binarySearch(ends, current_height);
        if (index == ends.size()) ends.push_back(current_height);
        else ends[index] = current_height;
        nvp[i] = index + 1;
    }
    int max_length = *std::max_element(nvp.begin(), nvp.end());
    cout << max_length;
}
