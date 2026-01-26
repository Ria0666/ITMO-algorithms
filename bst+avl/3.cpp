#include <iostream>
using namespace std;

class Tree {
public:
    long long x;
    long long lvl;
    Tree* leftkid;
    Tree* rightkid;
    Tree* parent = nullptr;

public:
    Tree(long long x) {
        this->x = x;
        this->leftkid = nullptr;
        this->rightkid = nullptr;
        this->lvl = 1;
    }
};

class FullTree {
public:
    Tree* root = nullptr;

    void add(long long x) {
        Tree* node = new Tree(x);

        if (root == nullptr) {
            root = node;
            return;
        }

        Tree* element = root;
        while (element != nullptr) {
            node->parent = element;
            if (node->x < element->x) {
                element->lvl++;
                element = element->leftkid;
            } else {
                element->lvl++;
                element = element->rightkid;
            }
        }

        if (node->parent == nullptr)
            root = node;
        else {
            if (node->x < node->parent->x)
                node->parent->leftkid = node;
            else
                node->parent->rightkid = node;
        }
    }

    void deleteNode(long long x) {
        Tree* node = exists(x);
        if (node == nullptr) {
            return;
        }

        Tree* prev;
        Tree* element;
        Tree* del = exists(x);
        if (del->leftkid == nullptr || del->rightkid == nullptr)
            prev = del;
        else
            prev = successor(x);

        if (prev->leftkid != nullptr)
            element = prev->leftkid;
        else
            element = prev->rightkid;

        if (element != nullptr)
            element->parent = prev->parent;

        if (prev->parent == nullptr)
            root = element;
        else {
            if (prev == prev->parent->leftkid)
                prev->parent->leftkid = element;
            else
                prev->parent->rightkid = element;
        }

        if (prev != del)
            del->x = prev->x;

        deleteLevel(prev);
        delete prev;
    }

    Tree* successor(long long x) {
        Tree* element = root;
        Tree* successor = nullptr;
        while (element != nullptr) {
            if (element->x > x) {
                successor = element;
                element = element->leftkid;
            } else
                element = element->rightkid;
        }
        return successor;
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

    int searchLenRight(Tree* node) {
        if (node == nullptr) return 0;
        else {
            return 1 + searchLenRight(node->rightkid);
        }
    }

    int searchLenLeft(Tree* node) {
        if (node == nullptr) return 0;
        else {
            return 1 + searchLenLeft(node->leftkid);
        }
    }

    long long findKthMax(Tree* node, long long k) {
        if (node == nullptr) return -1;
        
        long long rightCount = (node->rightkid) ? node->rightkid->lvl : 0;
        if (k == rightCount + 1) {
            return node->x;
        } else if (k <= rightCount) {
            return findKthMax(node->rightkid, k);
        } else {
            return findKthMax(node->leftkid, k - rightCount - 1);
        }
    }

    void deleteLevel(Tree* node) {
        while (node != nullptr) {
            node->lvl--;
            node = node->parent;
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    FullTree tree;
    long long n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        long long command, element;
        cin >> command >> element;
        if (command == 1)
            tree.add(element);
        else if (command == 0) {
            Tree* node = tree.root;
            cout << tree.findKthMax(node, element) << "\n";
        } else if (command == -1)
            tree.deleteNode(element);
    }

}

