#pragma once
#include <string>
#include <vector>
#include "trie.h"
#include "parser.h"
using namespace std;

// Search result
struct TrieResult{
    bool found;
    string translate;
    long long time;
};

class TrieOperations{
private:
    Trie trie;
public:
    long long parser_trie(const vector<entry>& dataset);
    TrieResult search_word(const string& word);
};