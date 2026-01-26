#include <iostream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

map<char, int> Frequencies(const string &input) {
    map<char, int> frequencies;
    for (char c : input) frequencies[c]++;
    return frequencies;
}

double arithmeticEncode(string &input) {
    double low = 0.0;
    double high = 1.0;
    double range;
    auto frequencies = Frequencies(input);
    map<char, pair<double, double>> probabilities;
    double c = 0.0;
    for (auto &[character, freq] : frequencies) {
        double prob = (double)freq / (double)input.size();
        probabilities[character] = std::make_pair(c, c + prob);
        c += prob;
    }
    for (char c : input) {
        range = high - low;
        high = low + range * probabilities[c].second;
        low = low + range * probabilities[c].first;
    }
    return low;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin>>s;
    double encoded = arithmeticEncode(s);
    cout << fixed << setprecision(6) << encoded << endl;
}
