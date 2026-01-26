#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Tree {
public:
    string x;
    int balance;
    Tree* leftkid;
    Tree* rightkid;

public:
    Tree(string x) : x(x), leftkid(nullptr), rightkid(nullptr), balance(0) {}
};

class avl {
public:
    Tree *root = nullptr;

    int height(Tree *node) {
        if (node == nullptr) return 0;
        else return node->balance;
    }

    void updateBalance(Tree *node) {
        if (node != nullptr) {
            node->balance = max(height(node->rightkid), height(node->leftkid)) + 1;
        }
    }

    void rotateLeft(Tree *&node) {
        Tree *rightTree = node->rightkid;
        Tree *leftTreeForRight = rightTree->leftkid;
        rightTree->leftkid = node;
        node->rightkid = leftTreeForRight;
        node = rightTree;
        updateBalance(node->leftkid);
        updateBalance(node);
    }

    void rotateRight(Tree *&node) {
        Tree *leftTree = node->leftkid;
        Tree *rightTreeForLeft = leftTree->rightkid;
        leftTree->rightkid = node;
        node->leftkid = rightTreeForLeft;
        node = leftTree;
        updateBalance(node->rightkid);
        updateBalance(node);
    }

    Tree *insert(Tree *node, const string &data) {
        if (node == nullptr) return new Tree(data);

        if (data > node->x) {
            node->rightkid = insert(node->rightkid, data);
        } else if (data < node->x) {
            node->leftkid = insert(node->leftkid, data);
        } else {
            return node;
        }

        updateBalance(node);

        if (height(node->rightkid) - height(node->leftkid) > 1) {
            if (data > node->rightkid->x)
                rotateLeft(node);
            else {
                rotateRight(node->rightkid);
                rotateLeft(node);
            }
        } else if (height(node->leftkid) - height(node->rightkid) > 1) {
            if (data < node->leftkid->x)
                rotateRight(node);
            else {
                rotateLeft(node->leftkid);
                rotateRight(node);
            }
        }

        return node;
    }

    void add(string &data) {
        root = insert(root, data);
    }

    Tree *search(Tree *node, const string &key) {
        if (node == nullptr || node->x == key) {
            return node;
        }

        if (key < node->x) {
            return search(node->leftkid, key);
        } else {
            return search(node->rightkid, key);
        }
    }

    Tree *check(const string &key) {
        return search(root, key);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    avl first;
    avl second;
    avl third;
    vector<string> f;
    vector<string> s;
    vector<string> t;
    long long n;
    cin >> n;
    string k;
    int score[3]{};
    for (long long i = 0; i < n; i++) {
        cin >> k;
        first.add(k);
        f.push_back(k);
    }
    for (long long i = 0; i < n; i++) {
        cin >> k;
        second.add(k);
        s.push_back(k);
    }
    for (long long i = 0; i < n; i++) {
        cin >> k;
        third.add(k);
        t.push_back(k);
    }
    for (long long i = 0; i < n; i++) {
        string e = f[i];
        if (!second.check(e) && !third.check(e)) score[0] += 3;
        else if (second.check(e) && third.check(e)) score[0] += 0;
        else score[0] += 1;
    }
    for (long long i = 0; i < n; i++) {
        string t = s[i];
        if (!first.check(t) && !third.check(t)) score[1] += 3;
        else if (first.check(t) && third.check(t)) score[1] += 0;
        else score[1] += 1;
    }
    for (long long i = 0; i < n; i++) {
        string r = t[i];
        if (!first.check(r) && !second.check(r)) score[2] += 3;
        else if (first.check(r) && second.check(r)) score[2] += 0;
        else score[2] += 1;
    }
    for (int i = 0; i < 3; i++) cout << score[i] << " ";
}
