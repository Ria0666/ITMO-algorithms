#include <iostream>
using namespace std;
void summm(int* all, string number, int &k) {
    int size = number.size();
    for (int i = 0; i < size; i++) {
        int ykaz = 5000 - i - 1;
        all[ykaz] += number[size - 1 - i] - '0';
        if (k > ykaz) k = ykaz;
    }
}
void res(int* all,int &k) {
    for (int i = 4999; i >= k; i--) {
        if (all[i] > 9) {
            all[i - 1] += all[i] / 10;
            all[i] %= 10;
            if (k>i-1) {
                k=i-1;
            }
        }
    }
}
int main() {
    long long n;
    cin>>n;
    int all[5000]{};
    string number;
    int k = 4999;
    for (long long i = 0; i < n; i++) {
        cin >> number;
        summm(all, number, k);
    }
    res(all,k);
    for (int i = k; i < 5000; i++) cout << all[i];
}
