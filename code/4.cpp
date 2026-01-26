#include <iostream>
using namespace std;

int findMistake(const string& code) {
    int mistake = 0;
    for (int i = 0; i < code.size(); ++i)
        if (code[i] == '1')
            mistake ^= i + 1;
    return mistake;
}

void fixMistake(string& code, int mistake) {
    if (mistake)
        code[mistake - 1] ^= '0' ^ '1';
}

void processCode(string& code) {
    int len = code.size();
    int f = 0;
    int b = 1;
    for (int i = 0; i < len; ++i)
        if (i + 1 == b)
            b <<= 1;
        else
            code[f++] = code[i];
    code.resize(f);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    for (int k = 0; k < t; ++k) {
        string code;
        cin >> code;
        int mistake = findMistake(code);
        fixMistake(code, mistake);
        processCode(code);
        cout << code << "\n";
    }
}

