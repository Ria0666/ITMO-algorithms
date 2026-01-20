#include <iostream>
using namespace std;
void sort (string a[],string b[],int n) {
    for (int j = 1; j < n; j++){
        int i = j - 1;
        string key1 = a[j];
        string key2 = b[j];
        while (i >= 0 && b[i] > key2) {
            a[i + 1] = a[i];
            b[i + 1] = b[i];
            i--;
        }
        a[i + 1] = key1;
        b[i + 1] = key2;
    }
}
int main(){
    int n, k, t;
    cin >> n >> k >> t;
    string a[n];
    string b[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < t; i++){
        for (int y = 0; y < n; y++) {
            b[y]=a[y][k - 1 - i]+b[y];
        }
    }
    sort(a,b,n);
    for (int i = 0; i < n; i++){
        cout << a[i] << "\n";
    }
}

