#include <iostream>
#include <vector>
using namespace std;

class Tree{
public:
    string x;
    Tree* leftkid;
    Tree* rightkid;
    Tree* parent= nullptr;
public:
    Tree(string x) {
        this->x=x;
        this -> leftkid = nullptr;
        this -> rightkid = nullptr;
    }
};
class fullTree{
public:
    Tree *root = nullptr;

    void add(string x) {
        if(check(x)) return;
        Tree *node = new Tree(x);
        Tree *element = root;
        while (element != nullptr) {
            node -> parent = element;
            if (node->x < element->x) element = element->leftkid;
            else element = element->rightkid;
        }
        if(node -> parent == nullptr) root = node;
        else {
            if(node->x < node -> parent -> x) node -> parent -> leftkid = node;
            else node -> parent -> rightkid = node;
        }
    }
    Tree *exists(string x){
        Tree* element = root;
        while(element != nullptr && x != element -> x) {
            if(x < element -> x) element = element ->leftkid;
            else element = element -> rightkid;
        }
        return element;
    }

    bool check(string x){
        return exists(x) != nullptr;
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    fullTree first;
    fullTree second;
    fullTree third;
    vector<string> f;
    vector<string> s;
    vector<string> t;
    long long n;
    cin >> n;
    string k;
    int score[3] {};
    for(long long i = 0;i < n;i++){
        cin >> k;
        first.add(k);
        f.push_back(k);
    }
    for(long long i = 0;i < n;i++){
        cin >> k;
        second.add(k);
        s.push_back(k);
    }
    for(long long i = 0;i < n;i++){
        cin >> k;
        third.add(k);
        t.push_back(k);
    }
    for(long long i = 0;i < n;i++){
        string e = f[i];
        if(!second.check(e) && !third.check(e)) score[0] += 3;
        else if(second.check(e) && third.check(e)) score[0] += 0;
        else score[0] += 1;
    }
    for(long long i = 0;i < n;i++){
        string t = s[i];
        if(!first.check(t) && !third.check(t)) score[1] += 3;
        else if(first.check(t) && third.check(t)) score[1] += 0;
        else score[1] += 1;
    }
    for(long long i = 0;i < n;i++){
        string r = t[i];
        if(!first.check(r) && !second.check(r)) score[2] += 3;
        else if(first.check(r) && second.check(r)) score[2] += 0;
        else score[2] += 1;
    }
    for (int i = 0;i < 3;i++) cout << score[i] << " ";
}
