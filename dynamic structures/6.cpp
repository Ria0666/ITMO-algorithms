#include <iostream>
using namespace std;
int place(int a[],int distance,int n) {
    int last = a[0];
    int B = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] - last >= distance) {
            last = a[i];
            ++B;
        }
    }
    return B;
}

int main() {
    int n, k;
    cin>>n>>k;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin>>a[i];
    }
    int low = 0;
    int high = a[n-1] - a[0];
    int md = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (place(a,mid,n)>=k) {
            md = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout<<md;
}
