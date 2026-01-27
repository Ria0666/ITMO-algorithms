#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

bool isValid(const vector<string>& req) {
    if (req.size() != 8) return false;

    regex name("^[A-Z][a-z]*$");
    regex age("^[0-9]{2}$");
    regex phone(R"(^((8|\+7)[\- ]?)?(\(?\d{3}\)?[\- ]?)?[\d\- ]{7,10}$)");
    regex city("^g\\.[A-Z]{3},$");
    regex street("^ul\\.[A-Z][a-z]*,$");
    regex house("^d\\.[0-9]+$");

    return regex_match(req[0], name) && regex_match(req[1], name) && regex_match(req[2], name)
           && regex_match(req[3], age) && regex_match(req[4], phone)
           && regex_match(req[5], city) && regex_match(req[6], street)
           && regex_match(req[7], house);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int q;
    cin >> q;
    cin.ignore();

    vector<string> results;
    for (int i = 0; i < q; ++i) {
        string inp;
        getline(cin, inp);

        vector<string> req;
        string tmp;
        for (char ch : inp) {
            if (ch == ' ') {
                req.push_back(tmp);
                tmp.clear();
            } else {
                tmp.push_back(ch);
            }
        }
        req.push_back(tmp);

        results.push_back(isValid(req) ? "YES" : "NO");
    }

    for (const string& res : results) {
        cout << res << "\n";
    }
}

