#include <vector>
#include <iostream>
using namespace std;

int main() {
  string s;
  cin >> s;
  int n = s.length();
  vector<int> prefix(n);

  for (int i = 1; i < n; i++) {
    int value = prefix[i - 1];
    while (value > 0 && s[i] != s[value])
      value = prefix[value - 1];

    if (s[i] == s[value]) value++;
    prefix[i] = value;
  }

  for (int i : prefix)
    cout << i << " ";
}
