#include <iostream>
using namespace std;
class Stek {
public:
    char soo;
    Stek* next;
public:
    Stek(char soo) {
        this->soo=soo;
        this->next= NULL;
    }
};
class fullStek {
public:
    Stek *head, *tail;
public:
    fullStek() {
        this->head = this->tail = NULL;
    }
    void push_front(char soo) {
        Stek* node = new Stek(soo);
        node->next=head;
        head=node;
        if (tail==NULL) tail = node;
    }
    void pop() {
        Stek* temp = head;
        head = head->next;
        delete temp;
    }
    int empty() {
        Stek* node=head;
        if (head==NULL) return 1;
        else return 0;
    }
};
int main() {
    fullStek lst;
    int n;
    cin >> n;
    string stroka;
    cin >> stroka;
    for (int i = 0; i < n; i++) {
        char c = stroka[i];
        if (c == '(' || c == '{' || c == '[') {
            lst.push_front(c);
        } else {
            if (lst.empty()) {
                cout << "NO" << endl;
                return 0;
            }
            char top = lst.head->soo;
            lst.pop();
            if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    if (lst.empty()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}


