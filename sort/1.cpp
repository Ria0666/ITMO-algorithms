#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    int a[n];
    for (int i = 0; i<n;++i) {
        cin>>a[i];
    }
    int i,key;
    for (int j=1;j<n;++j) {
        key=a[j];
        i=j-1;
        while (i>=0 && a[i] > key) {
            a[i+1] = a[i];
            i=i-1;
        }
        a[i+1]=key;
    }
    for (int p=0;p<n;++p) {
        cout<<a[p]<<" ";
    }
}
