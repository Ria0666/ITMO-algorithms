#include <iostream>
#include <list>
#include <map>
using namespace std;
class Node {
public:
    int pos;
    char next;
public:
    Node(int pos, char next) {
        this->pos=pos;
        this->next=next;
    }
};
list<Node> LZ78(string& s) {
    string pre;
    map<string, int> d;
    list<Node> ans;
    for(auto c : s) {
        if(d.find(pre + c) != d.end()) pre += c;
        else {
            ans.emplace_back(Node(d[pre], c));
            d[pre + c] = (int)d.size();
            pre = "";
        }
    }
    if(!pre.empty()) ans.push_back({d[pre], '\0'});
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string string;
    cin >> string;
    list<Node> lz78 = LZ78(string);
    for (auto code : lz78) {
        cout << code.pos << ' ' << code.next;
        if (code.next != '\0') cout << endl;
    }
}
