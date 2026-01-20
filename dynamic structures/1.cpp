#include <iostream>
using namespace std;
class Stek {
public:
    long long int soo;
    Stek* next;
public:
    Stek(long long int soo) {
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
    void push_front(long long int soo) {
        Stek* node = new Stek(soo);
        node->next=head;
        head=node;
        if (tail==NULL) tail = node;
    }
    Stek* getAt(int k) {
        if (k<0) return NULL;
        Stek* node = head;
        return node;

    }
    void pop() {
        Stek* temp = head;
        head = head->next;
        delete temp;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    fullStek lst;
    long long int n;
    cin>>n;
    long long int arr[n];
    long long int soo;
    char znak;
    long long int s;
    for (long long int i=0;i<n;++i) {
        arr[i]=-745857395638;
    }
    for (long long int i=0;i<n;++i) {
        cin>>znak;
        if (znak=='+') {
            cin >> soo;
            lst.push_front(soo);
        }
        else {
            Stek* n=lst.getAt(0);
            s=(n!=NULL) ? n->soo : 0;
            arr[i]=s;
            lst.pop();
        }
    }
    for (long long int i=0;i<n;++i) {
        if (arr[i]!=-745857395638) cout<<arr[i]<<"\n";
    }
}
