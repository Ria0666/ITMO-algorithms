#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Tree {
public:
    long long x;
    Tree* leftkid;
    Tree* rightkid;
    Tree* parent = nullptr;

    Tree(long long x) {
        this->x = x;
        this->leftkid = nullptr;
        this->rightkid = nullptr;
    }
};

Tree* insertNode(Tree* root, long long x) {
    if (root == nullptr) {
        return new Tree(x);
    }

    if (x < root->x) {
        root->leftkid = insertNode(root->leftkid, x);
        root->leftkid->parent = root;
    } else {
        root->rightkid = insertNode(root->rightkid, x);
        root->rightkid->parent = root;
    }

    return root;
}

class FullTree {
public:
    Tree *root = nullptr;

    Tree* findLCA(Tree* root, long long n1, long long n2) {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->x > n1 && root->x > n2) {
            return findLCA(root->leftkid, n1, n2);
        }

        if (root->x < n1 && root->x < n2) {
            return findLCA(root->rightkid, n1, n2);
        }

        return root;
    }

    long long find(long long n1, long long n2) {
        Tree* lca = findLCA(root, n1, n2);

        if (lca != nullptr) {
            return lca->x;
        }

        return -1;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    FullTree tree;
    long long n;
    cin >> n;
    long long element;
    for (long long i = 0; i < n; ++i) {
        cin >> element;
        tree.root = insertNode(tree.root, element);
    }
    long long first;
    long long second;
    cin >> first >> second;
    long long itog = tree.find(first, second);
    cout << itog;
}
