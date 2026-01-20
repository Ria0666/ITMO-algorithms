#include <iostream>
using namespace std;

int main() {
    int n,m,k;
    cin>>n>>m>>k;
    long long int ex[n];
    for (int i=0;i<n;++i) {
        cin>>ex[i];
    }
    long long int mark[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> mark[i][j];
        }
    }
    long long itog[m];
    long long int it=0;
    int r=0;
    while (r!=m) {
        for (int i=0;i<n;++i) {
            it+=ex[i]*mark[r][i];
            it %= 1000000007;
        }
        itog[r]=it;
        it=0;
        r++;
    }
    while (k!=0) {
        int max=0;
        int final=0;
        for (int i=0;i<m;++i) {
            if (max<=itog[i]) {
                max=itog[i];
                final=i;
            }
        }
        cout<<final+1<<" ";
        itog[final]=0;
        k--;
    }
}
