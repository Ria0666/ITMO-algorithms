#include <iostream>
#include <string>
using namespace std;

int findMinMessageLength(const string& s) {
    int n = s.length();
    for (int len = 1; len <= n; ++len) {
        if (n % len == 0) {
            string sub = s.substr(0, len);
            bool valid = true;
            for (int i = len; i < n; i += len) {
                if (s.substr(i, len) != sub) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return len;
            }
        }
    }
    return n;
}

int main() {
    string s;
    cin >> s;
    int result = findMinMessageLength(s);
    cout << result << endl;
    return 0;
}

