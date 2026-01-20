#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    long long key;
    int deg;
    bool mark;
    Node* p;
    Node* ch;
    Node* l;
    Node* r;

    explicit Node(long long v)
        : key(v), deg(0), mark(false), p(nullptr), ch(nullptr), l(this), r(this) {}
};

class FiboHeap {
public:
    FiboHeap() : mn(nullptr), sz(0) {}
    ~FiboHeap() { wipe(); }

    FiboHeap(const FiboHeap&) = delete;
    FiboHeap& operator=(const FiboHeap&) = delete;

    Node* push(long long x) {
        Node* nd = new Node(x);
        addRoot(nd);
        ++sz;
        return nd;
    }

    long long popMin(bool& ok) {
        Node* z = mn;
        if (!z) {
            ok = false;
            return 0;
        }
        ok = true;

        if (z->ch) {
            vector<Node*> kids;
            takeCycle(z->ch, kids);
            for (Node* v : kids) {
                cutOut(v);
                v->p = nullptr;
                v->mark = false;
                addRoot(v);
            }
            z->ch = nullptr;
        }

        if (z->r == z) {
            mn = nullptr;
        } else {
            Node* nxt = z->r;
            cutOut(z);
            mn = nxt;
            rebuild();
        }

        --sz;
        long long ans = z->key;
        delete z;
        return ans;
    }

    void decKey(long long from, long long to) {
        if (from == to || to > from) return;

        Node* x = seek(from);
        if (!x) return;

        x->key = to;
        Node* par = x->p;
        if (par && x->key < par->key) {
            cut(x, par);
            cascade(par);
        }
        if (!mn || x->key < mn->key) mn = x;
    }

    void dumpKeys(vector<long long>& out) const {
        out.reserve(out.size() + sz);
        if (!mn) return;

        vector<Node*> st;
        st.push_back(mn);

        while (!st.empty()) {
            Node* start = st.back();
            st.pop_back();

            vector<Node*> cyc;
            takeCycle(start, cyc);

            for (Node* v : cyc) {
                out.push_back(v->key);
                if (v->ch) st.push_back(v->ch);
            }
        }
    }

    size_t size() const { return sz; }

private:
    Node* mn;
    size_t sz;

private:
    static void cutOut(Node* x) {
        x->l->r = x->r;
        x->r->l = x->l;
        x->l = x;
        x->r = x;
    }

    static void putAfter(Node* pos, Node* x) {
        x->r = pos->r;
        x->l = pos;
        pos->r->l = x;
        pos->r = x;
    }

    static void takeCycle(Node* start, vector<Node*>& out) {
        if (!start) return;
        Node* cur = start;
        do {
            out.push_back(cur);
            cur = cur->r;
        } while (cur != start);
    }

    void addRoot(Node* x) {
        x->p = nullptr;
        x->mark = false;

        if (!mn) {
            x->l = x;
            x->r = x;
            mn = x;
            return;
        }
        putAfter(mn, x);
        if (x->key < mn->key) mn = x;
    }

    void link(Node* y, Node* x) {
        cutOut(y);
        y->p = x;
        y->mark = false;

        if (!x->ch) {
            x->ch = y;
            y->l = y;
            y->r = y;
        } else {
            putAfter(x->ch, y);
            if (y->key < x->ch->key) x->ch = y;
        }
        ++x->deg;
    }

    void rebuild() {
        if (!mn) return;

        vector<Node*> roots;
        takeCycle(mn, roots);

        vector<Node*> A(64, nullptr);

        for (Node* w : roots) {
            if (w->p) continue;

            Node* x = w;
            size_t d = static_cast<size_t>(x->deg);

            while (true) {
                if (d >= A.size()) A.resize(A.size() * 2, nullptr);
                if (!A[d]) {
                    A[d] = x;
                    break;
                }

                Node* y = A[d];
                if (x->key > y->key) swap(x, y);

                link(y, x);
                A[d] = nullptr;
                d = static_cast<size_t>(x->deg);
            }
        }

        mn = nullptr;
        for (Node* v : A) {
            if (!v) continue;

            v->l = v;
            v->r = v;
            v->p = nullptr;
            v->mark = false;

            if (!mn) {
                mn = v;
            } else {
                putAfter(mn, v);
                if (v->key < mn->key) mn = v;
            }
        }
    }

    void cut(Node* x, Node* par) {
        if (x->r == x) {
            par->ch = nullptr;
        } else {
            if (par->ch == x) par->ch = x->r;
            cutOut(x);
        }
        --par->deg;

        x->p = nullptr;
        x->mark = false;
        addRoot(x);
    }

    void cascade(Node* y) {
        Node* par = y->p;
        if (!par) return;

        if (!y->mark) {
            y->mark = true;
            return;
        }
        cut(y, par);
        cascade(par);
    }

    Node* seek(long long k) const {
        if (!mn) return nullptr;

        vector<Node*> st;
        st.push_back(mn);

        while (!st.empty()) {
            Node* start = st.back();
            st.pop_back();

            vector<Node*> cyc;
            takeCycle(start, cyc);

            for (Node* v : cyc) {
                if (v->key == k) return v;
                if (v->ch) st.push_back(v->ch);
            }
        }
        return nullptr;
    }

    void wipe() {
        if (!mn) return;

        vector<Node*> st;
        st.push_back(mn);

        vector<Node*> all;
        all.reserve(sz);

        while (!st.empty()) {
            Node* start = st.back();
            st.pop_back();

            vector<Node*> cyc;
            takeCycle(start, cyc);

            for (Node* v : cyc) {
                all.push_back(v);
                if (v->ch) st.push_back(v->ch);
            }
        }

        for (Node* v : all) delete v;

        mn = nullptr;
        sz = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<unique_ptr<FiboHeap>> heaps;
    vector<string> out;
    out.reserve(1024);

    string cmd;
    while (cin >> cmd) {
        if (cmd == "create") {
            heaps.push_back(make_unique<FiboHeap>());
        } else if (cmd == "insert") {
            size_t i;
            long long x;
            cin >> i >> x;
            heaps[i]->push(x);
        } else if (cmd == "extract-min") {
            size_t i;
            cin >> i;
            bool ok = false;
            long long v = heaps[i]->popMin(ok);
            out.push_back(ok ? to_string(v) : "*");
        } else if (cmd == "merge") {
            size_t a, b;
            cin >> a >> b;

            auto h = make_unique<FiboHeap>();
            vector<long long> vals;

            if (a == b) {
                vals.reserve(heaps[a]->size());
                heaps[a]->dumpKeys(vals);
            } else {
                vals.reserve(heaps[a]->size() + heaps[b]->size());
                heaps[a]->dumpKeys(vals);
                heaps[b]->dumpKeys(vals);
            }

            for (long long x : vals) h->push(x);
            heaps.push_back(move(h));
        } else if (cmd == "decrease-key") {
            size_t i;
            long long from, to;
            cin >> i >> from >> to;
            heaps[i]->decKey(from, to);
        }
    }

    for (const string& s : out) cout << s << '\n';
    return 0;
}
