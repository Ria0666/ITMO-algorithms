#include <iostream>
using namespace std;
int main() {
    int n,k;
    cin>>n>>k;
    int a[n];
    for (int i=0;i<n;++i) {
        cin >> a[i];
    }
    if (k>0) {
        if (k>n) {
            k=k%n;
        }
        while (k!=0) {
            int key = a[n-1];
            for (int i = n-1; i >0; --i) {
                a[i] = a[i-1];
            }
            a[0]=key;
            k-=1;
        }
    }
    else if (k<0) {
        if (k+n<0){
            k=k%n;
        }
        while (k!=0) {
            int key = a[0];
            for (int i = 0; i < n; ++i) {
                a[i] = a[i + 1];
            }
            a[n-1] = key;
            k +=1;
        }
    }
    for (int i=0;i<n;++i) {
        cout << a[i] << " ";
    }
    return 0;
}
