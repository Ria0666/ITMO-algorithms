#include <iostream>
using namespace std;

int main() {
    long long int n;
    cin >> n;
    long long int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    long long int k=0;
    for (long long int i = 0; i < n; i++) {
        long long int f = 0;
        for (long long int j = 0; j < n - 1; j++) {
            if (a[j] - a[j + 1] == 1 && a[j]>a[j+1]) {
                cout << ":(";
                k = 1;
                break;
            } else if (a[j] > a[j + 1] + 1) {
                int key = a[j];
                a[j] = a[j + 1] + 1;
                a[j + 1] = key - 1;
                f++;
            }
        }
        if (f == 0) {
            break;
        }
        if (k==1) {
            break;
        }
    }
    if (k!=1) {
        for (long long int i=0;i<n;i++) {
            cout<<a[i]<<" ";
        }
    }
}
