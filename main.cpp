#include <iostream> 
#include <string>
#include <vector>
#include "parser.h"
using namespace std;

//temporary fake search functions (replaced by trie later)
string searchTrie(const vector<entry>& dataset, const string& word) {
    //Loop through dataset
    for (int i = 0; i < dataset.size(); i++) {
        //If the English word matches the search word, return the Spanish translation
        if (dataset[i].english == word) {
            return dataset[i].spanish;
        }
    }
    return "Word not found";
}

//Temporary search using dataset (will be replaced by Hash later)
string searchHash(const vector<entry>& dataset, const string& word) {
    //Loop through dataset
    for (int i = 0; i < dataset.size(); i++) {
        if (dataset[i].english == word) {
            return dataset[i].spanish;
        }
    }
    return "Word not found";    
}


int main() {
    //load data from data.scv file
    vector<entry> dataset = loadDataset("data.csv");

    //user input
    string word;
    cout << "Enter a word to search: ";
    cin >> word;

    //call search functions
    string trieResult = searchTrie(dataset, word);
    string hashResult = searchHash(dataset, word);

    //Temporary timing values (NEED TO REPLACE)
    long long trieTime = 120;
    long long hashTime = 80;

    //Print results
    cout << "Word: " << word << endl;
    cout << "TrieResult: " << trieResult << endl;
    cout << "TrieTime: " << trieTime << endl;
    cout << "HashResult: " << hashResult << endl;
    cout << "HashTime: " << hashTime << endl;

    return 0;

}