// Saved file
#include "trie.h"

// Base Initialization
TrieNode::TrieNode(){
    isWord = false;
    english = "";
    spanish = "";

    for (int i = 0; i < 256; i ++){
        children[i] = nullptr;
    }
}
// Establishing/Defining root
Trie::Trie(){
    root = new TrieNode();
}

//Insert
void Trie::insert(const string& english, const string& spanish){
    TrieNode* current = root;
    // Input is English
    for (int i = 0; i < english.length(); i ++){
        int index = (int)english[i];

        if (index < 0 || index >= 256){
            continue;
        }
        if (current->children[index] == nullptr){
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isWord = true;
    current->english = english;
    current->spanish = spanish;

    // Input is Spanish
    current = root;
    for (int i = 0; i < spanish.length(); i++){
        int index = (int)spanish[i];

        if (index < 0 || index >= 256){
            continue;
        }
        if (current->children[index] == nullptr){
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isWord = true;
    current->english = english;
    current->spanish = spanish;
}

// Search
bool Trie::search(const string& target, string& result){
    TrieNode* current = root;

    for( int i = 0; i < target.length(); i ++){
        int index = (int)target[i];

        // Checks for invalid indexes/nullptr
        if (index < 0 || index >= 256){
            return false;
        }
        if (current->children[index] == nullptr){
            return false;
        }

        current = current->children[index];
    }

    if (current->isWord){
        // If input is english output spanish
        if (target == current->english){
            result = current->spanish;
        }
        // But if input is spanish output english
        else{
            result = current->english;
        }
        return true;
    }
    return false;
}