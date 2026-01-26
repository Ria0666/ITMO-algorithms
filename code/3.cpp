#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Huffman {
public:
    char x;
    long long fr;
    Huffman* leftkid;
    Huffman* rightkid;
public:
    Huffman(char x, long long fr) {
        this->x=x;
        this->fr=fr;
        this->leftkid=nullptr;
        this->rightkid=nullptr;
    }
};

bool compareNodes(Huffman* left, Huffman* right) {
    return left->fr > right->fr;
}

Huffman* HuffmanTree(vector<long long>& arr) {
    vector<Huffman*> nodes;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > 0) {
            nodes.push_back(new Huffman(char(i), arr[i]));
        }
    }
    while (nodes.size() > 1) {
        sort(nodes.begin(), nodes.end(), compareNodes);
        Huffman* left = nodes.back();
        nodes.pop_back();
        Huffman* right = nodes.back();
        nodes.pop_back();
        Huffman* mergedNode = new Huffman('$', left->fr + right->fr);
        mergedNode->leftkid = left;
        mergedNode->rightkid = right;
        nodes.push_back(mergedNode);
    }
    return nodes.front();
}

void HuffmanCodes(Huffman* root, string code, vector<string>& codes) {
    if (root == nullptr) return;
    if (root->x != '$') codes[root->x] = code;
    HuffmanCodes(root->leftkid, code + "0", codes);
    HuffmanCodes(root->rightkid, code + "1", codes);
}

string encodeHuffman(string& input,vector<string>& codes) {
    string final;
    for (char c : input) final += codes[static_cast<int>(c)];
    return final;
}
vector<long long> calculate(string& input) {
    vector<long long> frequencies(256, 0);
    for (char c : input) frequencies[int(c)]++;
    return frequencies;
}
int main() {
    string String;
    cin>>String;
    vector<long long> frequencies= calculate(String);
    Huffman* root = HuffmanTree(frequencies);
    vector<string> huffmanCodes(256);
    HuffmanCodes(root, "", huffmanCodes);
    string encodedString = encodeHuffman(String, huffmanCodes);
    cout << encodedString.length() << "\n";
}

