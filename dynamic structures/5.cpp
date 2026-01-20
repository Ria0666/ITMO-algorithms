#include <iostream>
using namespace std;
class Zadach {
public:
    int x;
    int in;
    Zadach *next;
public:
    Zadach(int x, int in)
    {
        this->x=x;
        this->in=in;
    }
};
class fullStack {
public:
    Zadach *head;
public:
    fullStack() {
        this->head =NULL;
    }
    void push(int x, int in) {
        Zadach *node = new Zadach(x, in);
        node->next = head;
        head = node;
    }
    int pop() {
        Zadach *temp = head;
        int vsp = head->x;
        head = head->next;
        delete temp;
        return vsp;
    }
    int empty() {
        if (head==NULL) return 1;
        else return 0;
    }
};

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    fullStack stack;
    int r[n];
    for (int i = 0; i < n; i++) {
        while (stack.empty()==0 && arr[stack.head->in] < arr[i]) {
            r[stack.head->in] = i - stack.head->in;
            stack.pop();
        }
        stack.push(arr[i], i);
    }
    while (stack.empty()==0) {
        r[stack.head->in] = -1;
        stack.pop();
    }

    for (int i = 0; i < n; i++) {
        cout<<r[i]<< " ";
    }
}
