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

class fullTree {
public:
    Tree *root = nullptr;
    Tree* build(vector<long long>& forpre) {
        if (forpre.empty()) {
            return nullptr;
        }
        Tree* node = new Tree(forpre[0]);
        stack <Tree*> nodeStack;
        nodeStack.push(node);
        for (long long i = 1; i < forpre.size(); ++i) {
            Tree* current = nullptr;

            while (!nodeStack.empty() && forpre[i] >= nodeStack.top()->x) {
                current = nodeStack.top();
                nodeStack.pop();
            }

            if (current != nullptr) {
                current->rightkid = new Tree(forpre[i]);
                nodeStack.push(current->rightkid);
            } else {
                nodeStack.top()->leftkid = new Tree(forpre[i]);
                nodeStack.push(nodeStack.top()->leftkid);
            }
        }
        return node;
    }

    Tree *exists(long long x) {
        Tree *element = root;
        while (element != nullptr && x != element->x) {
            if (x < element->x)
                element = element->leftkid;
            else
                element = element->rightkid;
        }
        return element;
    }

    void preorder(Tree *node) {
        if (node == nullptr) return;
        cout << node->x;
        preorder(node->rightkid);
        preorder(node->leftkid);
    }

    void inorder(Tree* node,vector<long long> &forin) {
        if (node== nullptr) return;
        inorder(node->leftkid,forin);
        forin.push_back(node->x);
        inorder(node->rightkid,forin);
    }
    void postorder(Tree* node,vector<long long> &forpost) {
        if (node== nullptr) return;
        postorder(node->leftkid,forpost);
        postorder(node->rightkid,forpost);
        forpost.push_back(node->x);
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
    vector<long long> forpre;
    forpre.reserve(n);
    for (long long i = 0; i < n; ++i) {
        cin >> element;
        forpre.push_back(element);
    }
    vector<long long> forin;
    vector<long long> forpost;
    forin.reserve(n);
    forpost.reserve(n);
    Tree* root = tree.build(forpre);
    tree.inorder(root,forin);
    tree.postorder(root,forpost);
    for (long long i=0;i<n;++i) {
        cin >> element;
        if (forin[i] != element) {
            cout << "NO";
            return 0;
        }
    }
    for (long long i=0;i<n;++i) {
        cin >> element;
        if (forpost[i] != element) {
            cout << "NO";
            return 0;
        }

    }
    cout<<"YES";
}
