#include <iostream>
using namespace std;
void sort(long long int a[], long long b[], int left, int right) {
    if (left == right) return;
    int mid = left + (right - left) / 2;
    sort(a, b, left, mid);
    sort(a, b, mid + 1, right);
    for (int i = left; i <= right; i++)
        b[i] = a[i];
    int left2 = left, right2 = mid + 1;
    for (int i = left; i <= right; i++) {
        if (right2 > right || left2 <= mid && b[left2] <= b[right2])
            a[i] = b[left2++];
        else
            a[i] = b[right2++];
    }
}
int main() {
    long long n, k;
    cin>>n>>k;
    long long w[n];
    long long m[n];
    long long tmp[n];
    for (int i = 0; i < n; i++) {
        cin>>w[i];
    }
    for (int i = 0; i < n; i++) {
        cin>>m[i];
    }
    sort(w,tmp,0,n-1);
    sort(m,tmp,0,n-1);
    long long l = w[0] + m[0];
    long long r = w[n - 1] + m[n - 1];
    while (l < r) {
        long long mid = (l + r) / 2;
        long long count = 0;
        for (int i = 0; i < n; i++) {
            long long low = 0, high = n - 1;
            long long index = -1;
            while (low <= high) {
                int midd = low + (high - low) / 2;
                if (m[midd] + w[i] <= mid) {
                    index = midd;
                    low = midd + 1;
                } else {
                    high = midd - 1;
                }
            }
            if (index == -1) {
                break;
            }
            count += (index + 1);
        }
        if (count >= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l;
}
