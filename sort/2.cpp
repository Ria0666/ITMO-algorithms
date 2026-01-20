#include <iostream>
using namespace std;
void sort (int a[], int l, int r) {
    int l2=l;
    int r2=r;
    int point = a[rand() % (r2 - l2 + 1) + l2];
    while (l2 <= r2) {
        while (a[l2] < point) {
            l2++;
        }
        while (a[r2] > point) {
            r2--;
        }
        if (l2 <= r2) {
            int key = a[l2];
            a[l2]=a[r2];
            a[r2]=key;
            l2++;
            r2--;
        }
    }
    if (l < r2) {
        sort(a, l, r2);
    }
    if (r > l2) {
        sort(a, l2, r);
    }
}

int main() {
    int n;
    cin>>n;
    int a[n];
    for (int i = 0; i<n;++i) {
        cin>>a[i];
    }
    sort(a,0,n-1);
    for (int i=0;i<n;++i) {
        cout<<a[i]<<" ";
    }
}
