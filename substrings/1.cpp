#include <iostream>
#include <vector>
using namespace std;

vector<int> findPos(string text, string pat) {
    int textLen = text.size();
    int patLen = pat.size();
    vector<int> positions;

    for (int i = 0; i < textLen; i++) {
        if (text[i] == pat[0]) {
            if (patLen != 1)
                for (int j = 1; j < patLen; j++) {
                    if (text[i + j] == pat[j]) {
                        if (j == patLen - 1)
                            positions.push_back(i);
                        continue;
                    }
                    else break;
                }
            else
                positions.push_back(i);
        }
    }
    return positions;
}

int main() {
    string text;
    string pat;
    cin >> text >> pat;

    vector<int> result;
    result = findPos(text, pat);

    cout << result.size() << "\n";
    for (int idx : result)
        cout << idx << " ";
}

