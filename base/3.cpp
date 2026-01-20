#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    int den[n];
    for (int i = 0; i < n; ++i) {
        cin >> den[i];
    }
    int f=-1;
    int t=0;
    int o=0;
    for (int i=1; i<n;++i) {
       o=o+den[i];
    }
    for (int i=0;i<n;++i) {
        if (t==o) {
            f=i;
            break;
        }
        t=t+den[i];
        o=o-den[i+1];
    }
    cout<<f;
    return 0;
}
