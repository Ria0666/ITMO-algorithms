#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<long long>> queues;
void create() {
    vector<long long> newQueue;
    queues.push_back(newQueue);
    newQueue.clear();
}
void sort(vector<long long>& q) {
    vector<long long> temp;
    while (!q.empty()) {
        temp.push_back(q.front());
        q.erase(q.begin());
    }
    sort(temp.begin(), temp.end());
    for (long long i : temp) {
        q.push_back(i);
    }
    temp.clear();
}
void insert(long long k, long long x) {
    queues[k].push_back(x);
}
long long int extractmin(long long k) {
    sort(queues[k]);
    long long b;
    if (queues[k].empty()) {
        b = 00;
    } else {
        b = queues[k].front();
        queues[k].erase(queues[k].begin());;
    }
    return b;
}
void merge(long long k, long long m) {
    vector<long long> mergedQueue;
    vector<long long> copy1=queues[k];
    vector<long long> copy2=queues[m];
    while (!copy1.empty() && !copy2.empty()) {
        if (copy1.front() < copy2.front()) {
            mergedQueue.push_back(copy1.front());
            copy1.erase(copy1.begin());
        } else {
            mergedQueue.push_back(copy2.front());
            copy2.erase(copy2.begin());
        }
    }
    while (!copy1.empty()) {
        mergedQueue.push_back(copy1.front());
        copy1.erase(copy1.begin());
    }
    while (!copy2.empty()) {
        mergedQueue.push_back(copy2.front());
        copy2.erase(copy2.begin());
    }
    queues.push_back(mergedQueue);
    copy1.clear();
    copy2.clear();
    mergedQueue.clear();
}

void decreasekey(long long k, long long x, long long y) {
    vector<long long> temp;
    int time=1;
    while (!queues[k].empty()) {
        if (queues[k].front() == x && time>0) {
            temp.push_back(y);
            time--;
        } else {
            temp.push_back(queues[k].front());
        }
        queues[k].erase(queues[k].begin());
    }
    queues[k] = temp;
    temp.clear();
}
int main() {
    queues.reserve(1000000);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    string operation;
    long long k,x,m,y,dd;
    while (cin >> operation) {
        if (operation == "create") {
            create();
        } else if (operation == "insert") {
            cin >> k >> x;
            insert(k, x);
        } else if (operation == "extract-min") {
            cin >> k;
            dd=extractmin(k);
            if (dd==00) {
                cout<<"*"<<"\n";
            }
            else cout<<dd<<"\n";
        } else if (operation == "merge") {
            cin >> k >> m;
            merge(k, m);
        } else if (operation == "decrease-key") {
            cin >> k >> x >> y;
            decreasekey(k, x, y);
        }
    }
    queues.clear();
}
