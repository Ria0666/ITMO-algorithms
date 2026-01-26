#include <iostream>
#include <vector>
using namespace std;
struct Tree {
    int height = 1;
    int x = 0;
    int lkid_height = height;
    int rkid_height = height;
    Tree* parent = nullptr;
};

void calculateHeights(Tree& node) {
    if (node.parent != nullptr) node.height = node.parent->height + 1;
    
    node.rkid_height = node.height;
    node.lkid_height = node.height;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<Tree> tree(n);
    for (int i = 0; i < n; ++i) {
        int x, l, r;
        cin >> x >> l >> r;
        tree[i].x = x;

        if (l > 0) tree[l - 1].parent = &tree[i];
        if (r > 0) tree[r - 1].parent = &tree[i];
        calculateHeights(tree[i]);
    }

    for (int i = n - 1; i > 0; --i) {
        if (tree[i].x > tree[i].parent->x) tree[i].parent->rkid_height = tree[i].height;
        else tree[i].parent->lkid_height = tree[i].height;

        if (tree[i].height > tree[i].parent->height) tree[i].parent->height = tree[i].height;
    }
    for (int i = 0; i < n; ++i) cout << tree[i].rkid_height - tree[i].lkid_height << '\n';
}
