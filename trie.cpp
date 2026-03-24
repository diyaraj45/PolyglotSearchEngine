//Bug fix + Implementation
#include "trie.h"
#include <cctype>

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

// Convert String to LowerCase
string lower_case(const string& input){
    string result = input;

    for (int i = 0; i < result.length(); i++){
        result[i] = tolower((unsigned char)result[i]);
    }
    return result;
}

//Insert
void Trie::insert(const string& english, const string& spanish){
    // LowerCase conversion
    string eng = lower_case(english);
    string spa = lower_case(spanish);

    TrieNode* current = root;
    // Input is English
    for (int i = 0; i < eng.length(); i ++){
        //Not int because int can be negative
        int index = (unsigned char)eng[i];

        if (current->children[index] == nullptr){
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isWord = true;
    current->english = eng;
    current->spanish = spa;

    // Input is Spanish
    current = root;
    for (int i = 0; i < spa.length(); i++){
        int index = (unsigned char)spa[i];

        if (current->children[index] == nullptr){
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isWord = true;
    current->english = eng;
    current->spanish = spa;
}

// Search
bool Trie::search(const string& target, string& result){
    string word = lower_case(target);

    TrieNode* current = root;

    for( int i = 0; i < word.length(); i ++){
        int index = (unsigned char)word[i];

        // Checks for nullptr
        if (current->children[index] == nullptr){
            return false;
        }
        current = current->children[index];
    }

    if (current->isWord){
        // If input is english output spanish
        if (word == current->english){
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