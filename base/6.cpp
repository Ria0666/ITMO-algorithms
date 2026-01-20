#include "iostream"

using namespace std;

int main() {
    int n, i, count, block;
    cin >> n;
    int rooms[n];
    for (i = 0; i < n; i++) {
        cin >> rooms[i];
    }
    block = rooms[n - 1];
    for (int j = 0; j < 2; j++){
        count = 0;
        for (i = 0; i < n; i++) {
            if ((block & rooms[i]) != 0) {
                count++;
                block = rooms[i];
            } else {
                block = block | rooms[i];
            }
        }
    }
    cout << count;
}
