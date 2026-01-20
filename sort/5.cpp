#include <iostream>
using namespace std;
long long Count  = 0;
void mergeSort(int* a, int* vsp, int left, int right) {
    if (left == right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, vsp, left, mid);
    mergeSort(a, vsp, mid + 1, right);
    for (int i = left; i <= right; i++)
        vsp[i] = a[i];
    int l = left, r = mid + 1;
    for (int i = left; i <= right; i++) {
        if (r > right || (l <= mid && vsp[l] <= vsp[r]))
            a[i] = vsp[l++];
        else {
            a[i] = vsp[r++];
            Count += mid + 1 - l;
        }
    }
}
int main() {
    int n;
    cin >>n;
    int a[n];
    int vsp[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    mergeSort(a, vsp, 0, n - 1);
    cout << Count << "\n";
}
