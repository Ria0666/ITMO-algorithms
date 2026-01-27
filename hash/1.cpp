#include <iostream>
#include <vector>
using namespace std;


long long hash_function(long long x) {
    return x % 1000007;
}

int main() {
    long long n;
    cin >> n;

    vector<long long> hash_table1(1000007,0);
    vector<long long> hash_table2(1000007,0);
    long long value;
    
    for (long long i = 0; i < n; i++) {
        cin >> value;
        ++hash_table1[hash_function(value)];
    }
    
    for (long long i = 0; i < n; i++) {
        cin >> value;
        ++hash_table2[hash_function(value)];
    }
    
    bool are_equal = true;
    for (long long i = 0; i < 1000007; i++) {
        if (hash_table1[i] != hash_table2[i]) {
            are_equal = false;
            break;
        }
    }

    if (are_equal) 
        cout << "YES" << endl;
    else 
        cout << "NO" << endl;
}

