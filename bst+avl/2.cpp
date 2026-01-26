#include <iostream>
using namespace std;

class Tree{
public:
    long long x;
    Tree* leftkid;
    Tree* rightkid;
    Tree* parent= nullptr;
public:
    Tree(long long x) {
        this->x=x;
        this -> leftkid = nullptr;
        this -> rightkid = nullptr;
    }
};
class fullTree{
public:
    Tree *root = nullptr;

    void add(long long x) {
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

    void delet(long long x) {
        Tree* node = exists(x);
        if(node == nullptr){
            return;
        }
        Tree* prev;
        Tree* element;
        Tree* del = exists(x);
        if (del -> leftkid == nullptr || del -> rightkid == nullptr) prev = del;
        else prev = successor(x);

        if (prev -> leftkid != nullptr) element = prev -> leftkid;
        else element = prev -> rightkid;

        if (element != nullptr) element -> parent = prev -> parent;

        if (prev -> parent == nullptr) root = element;
        else {
            if (prev == prev -> parent -> leftkid)
                prev -> parent -> leftkid = element;
            else
                prev -> parent -> rightkid = element;
        }

        if (prev != del) del -> x = prev -> x;
        delete prev;
    }

    Tree* successor(long long x){
        Tree* element = root;
        Tree* successor = nullptr;
        while(element != nullptr){
            if(element -> x > x) {
                successor = element;
                element = element->leftkid;
            }
            else element = element -> rightkid;
        }
        return successor;
    }

    Tree *exists(long long x){
        Tree* element = root;
        while(element != nullptr && x != element -> x) {
            if(x < element -> x) element = element ->leftkid;
            else element = element -> rightkid;
        }
        return element;
    }

    Tree* parentcerch(long long x) {
        Tree* node = root;
        Tree* par = nullptr;
        while (node != nullptr) {
            if (node->x < x) {
                par = node;
                node = node->rightkid;
            } else node = node->leftkid;
        }
        return par;
    }

    bool check(long long x){
        return exists(x) != nullptr;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string command;
    fullTree tree;
    long long x;
    while (cin >> command) {
        if(command == "insert"){
            cin >> x;
            tree.add(x);
        }
        else if(command == "delete"){
            cin >> x;
            Tree* check = tree.exists(x);
            if(check != nullptr) {
                tree.delet(x);
            }
        }
        else if(command == "exists"){
            cin >> x;
            if (tree.check(x)) cout<<"true"<<"\n";
            else cout<<"false"<<"\n";
        }
        else if(command == "next"){
            cin >> x;
            Tree* check = tree.successor(x);
            if(check != nullptr) cout << check -> x << '\n';
            else cout << "none" << '\n';
        }
        else if(command == "prev"){
            cin >> x;
            Tree* check = tree.parentcerch(x);
            if(check != nullptr) cout << check -> x << '\n';
            else cout << "none" << '\n';
        }
    }
}
