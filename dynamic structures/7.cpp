#include <iostream>
using namespace std;
class Node {
public:
    long long int x;
    long long int h;
    Node* next;
    Node(int x, int h, Node* next = NULL) : x(x), h(h), next(next) {}
};

class Stek {
public:
    Node* head;
public:
    Stek() {
        this->head = NULL;
    }
    void push(int x, int height) {
        Node* node = new Node(x, height, head);
        head = node;
    }
    void pop() {
        if (head!=NULL) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};
int main() {
    int n;
    cin >> n;
    int arr[n+2];
    arr[0] = -1;
    arr[n+1] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    Stek lst;
    lst.push(0, -1);
    long long max = 0;
    for (int i = 1; i <= n + 1; ++i) {
        int verh = arr[i];
        int y = i;
        while (verh <= lst.head->h) {
            y = lst.head->x;
            int p = lst.head->h;
            lst.pop();
            long long area = 1LL * p * (i - y);
            if (area > max) {
                max = area;
            }
        }
        lst.push(y, verh);
    }
    cout << max;
}
