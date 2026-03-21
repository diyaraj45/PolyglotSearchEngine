// Saved file
#include <iostream>
#include <string>
using namespace std;

struct TrieNode{
    TrieNode* children[256]; //ASCII 128 could cause issues with ! && ? found in data set
    bool isWord;

    string english;
    string spanish;

    TrieNode();
};

class Trie{
private:
    TrieNode* root;

 public:
    Trie();

    void insert(const string& english, const string& spanish);
    bool search(const string& target, string& result);
};
