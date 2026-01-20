#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0,j=1; i <= n;++i,++j)
    {
        a[i]=j;
    }
    for (int i = 2; i < n;++i) {
        int key=a[i];
        a[i]=a[i/2];
        a[i/2]=key;
    }
    for (int i=0;i<n;++i) {
        cout<<a[i]<<" ";
    }
}
