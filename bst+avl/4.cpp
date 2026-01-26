#include <iostream>
#include <vector>
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

class fullTree {
public:
    Tree* root = nullptr;

    void add(long long x) {
        if (check(x)) return;
        Tree* node = new Tree(x);
        Tree* element = root;
        while (element != nullptr) {
            node->parent = element;
            if (node->x < element->x) {
                if (element->leftkid == nullptr) {
                    element->leftkid = node;
                    break;
                }
                element = element->leftkid;
            } else {
                if (element->rightkid == nullptr) {
                    element->rightkid = node;
                    break;
                }
                element = element->rightkid;
            }
        }
        if (node->parent == nullptr) root = node;
    }

    Tree* exists(long long x) {
        Tree* element = root;
        while (element != nullptr && x != element->x) {
            if (x < element->x)
                element = element->leftkid;
            else
                element = element->rightkid;
        }
        return element;
    }

    bool check(long long x) {
        return exists(x) != nullptr;
    }

    void preorder(Tree* node, int depth, int& maxDepth) {
        if (node == nullptr) return;
        if (depth > maxDepth) {
            cout << node->x << " ";
            maxDepth = depth;
        }
        preorder(node->rightkid, depth + 1, maxDepth);
        preorder(node->leftkid, depth + 1, maxDepth);
    }

    void preorderstart() {
        int maxDepth = -10000000;
        preorder(root, 0, maxDepth);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    fullTree tree;
    long long n;
    cin >> n;
    long long element;
    for (long long i = 0; i < n; ++i) {
        cin >> element;
        tree.add(element);
    }
    tree.preorderstart();
}
