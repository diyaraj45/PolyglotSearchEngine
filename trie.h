#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TrieNode{
    TrieNode* children[256]; //ASCII 128 could cause issues with ! && ? found in data set
    bool isWord;

    string english;
    vector<string> spanish; // Due to many translations of a single word in english (Ex: Vete, Vaya, ...)

    TrieNode();
};

class Trie{
private:
    TrieNode* root;

 public:
    Trie();

    void insert(const string& english, const string& spanish);
    bool search(const string& target, vector<string>& results);
};
