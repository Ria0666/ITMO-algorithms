#include <iostream>
using namespace std;


int checkout (long long int a[],long long int n) {
    for (int i=0;i<(n-1)/2; i++) {
        if (!((a[i]<=a[2*i+1]) || (a[i]<=a[2*i+2]))) return 0;
    }
    return 1;
}
int main() {
    long long int n;
    cin>>n;
    long long int a[n];
    for (int i=0;i<n;++i) {
      cin>>a[i];
    }
    if(checkout(a,n)==1) {
        cout<<"YES";
    }
    else {
        cout<<"NO";
    }
}
