#include "blazingio.hpp"
#include <string>
#include <map>

using namespace std;

struct Node {
    map<char, Node*> children;
    bool isEnd;
    int count;
    int wordCount;
};

struct Trie {
    Node* root;
    int totalWords;

    Trie() {
        root = new Node{{}, false, 0, 0};
        totalWords = 0;
    }

    void insert(string& word) {
        Node* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end())
                current->children[c] = new Node{{}, false, 0, 0};

            current = current->children[c];
            current->count++;
        }

        current->isEnd = true;
        current->wordCount++;
        totalWords++;
    }

    string find(int index) {
        if (index > totalWords)  return "";

        Node* current = root;
        string result;
        int currentIndex = 0;

        while (currentIndex < index) {
            for (auto& [charKey, node] : current->children) {
                if (currentIndex + node->count >= index) {
                    result.push_back(charKey);
                    current = node;
                    if (current->isEnd)
                        currentIndex += current->wordCount;
                    break;
                } else {
                    currentIndex += node->count;
                }
            }
        }
        return result;
    }
};

int main() {
    int n;
    cin >> n;

    Trie trie;

    for (int i = 0; i < n; ++i) {
        string input;
        cin >> input;
        if (isalpha(input[0])) 
            trie.insert(input);
        else {
            int k = stoi(input);
            cout << trie.find(k) << '\n';
        }
    }
}

