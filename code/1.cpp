#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    long long n;
    cin >> n;
    vector<string> code;
    code.push_back("0");
    code.push_back("1");
    long long kolvo = 2;
    for (long long i = kolvo; i < (1<<n); i *= 2) {
        vector<string> foriteration;
        for (long long j = 0; j < i; j++) 
            foriteration.push_back("0" + code[j]);
            for (long long j = i - 1; j >= 0; j--)
                foriteration.push_back("1" + code[j]);
            code=foriteration;
            foriteration.clear();
    }
    for (long long i = 0; i < code.size(); i++) {
        cout << code[i] << endl;
    }
}
