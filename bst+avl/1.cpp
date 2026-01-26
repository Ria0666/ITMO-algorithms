#include <iostream>
#include <vector>
using namespace std;

struct Tree {
    int x;
    Tree* leftkid;
    Tree* rightkid;
    Tree(int val) : x(val), leftkid(nullptr), rightkid(nullptr) {}
};

Tree* sorted(vector<long long>& nums, long long start, long long end) {
    if (start > end) {
        return nullptr;
    }
    int mid = start + (end - start) / 2;
    Tree* root = new Tree(nums[mid]);
    root->leftkid = sorted(nums, start, mid - 1);
    root->rightkid = sorted(nums, mid + 1, end);
    return root;
}

void preorder(Tree* root) {
    if (root != nullptr) {
        cout << root->x << " ";
        preorder(root->leftkid);
        preorder(root->rightkid);
    }
}

int main() {
    long long n;
    cin>>n;
    vector <long long> arr;
    arr.reserve(n);
    long long element;
    for (long long i=0;i<n;++i) {
        cin>>element;
        arr.push_back(element);
    }
    Tree* root = sorted(arr, 0, n - 1);
    preorder(root);
}
