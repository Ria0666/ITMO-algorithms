#include <iostream>
using namespace std;

int main() {
    long long int n,m;
    cin>>n>>m;
    if (m>n) m=n;
    long long int sokrov[n];
    long long int symka[m];
    for (long long int i=0;i<n;++i) {
        cin>>sokrov[i];
    }
    for (long long int i=0;i<m;++i) {
        symka[i]=sokrov[i];
    }
    for (long long int i=m;i<n;++i) {
        long long int dno=symka[0];
        long long int verh=symka[m-1];
        for (long long int i=0;i<m-2;++i) {
            symka[i]=symka[i+1];
        }
        if (sokrov[i]>=dno && sokrov[i]>=verh) {
            symka[m-1] = sokrov[i];
            if (verh>dno) {
                symka[m - 2] = verh;
            }
            else  {
                symka[m - 2] = dno;
            }
        }
        else if (dno>=sokrov[i] && dno>=verh) {
            symka[m-1]=dno;
            if (verh>sokrov[i]) {
                symka[m-2]=verh;
            }
            else {
                symka[m-2]=sokrov[i];
            }
        }
        else if (verh>=dno && verh>=sokrov[i]) {
            symka[m-1]=verh;
            if (dno>sokrov[i]) {
                symka[m-2]=dno;
            }
            else {
                symka[m-2]=sokrov[i];
            }
        }
    }
    for (long long int i=0;i<m;++i) {
        cout<<symka[i]<<" ";
    }
}
