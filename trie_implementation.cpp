#include "trie_implementation.h"
#include "timer.h"

#include <iostream>
#include <sstream> // Joins vector<string>!

// Loading the dataset of the english to spanish word pairs into the trie (+timer)
long long TrieOperations::parser_trie(const vector<entry>& dataset){
    Timer timer;
    // Start timer
    timer.start();

    // Loop through the dataset
    // size_t (sizeof operator) (unsigned int)
    for (size_t i = 0; i < dataset.size(); i++){
        for (size_t j = 0; j < dataset[i].spanish.size(); j++){
            trie.insert(dataset[i].english, dataset[i].spanish[j]);
        }
    }
    // Return time took
    return timer.stop();
}

// Trie search: searches for the inserted word, if found is found in the dataset the translation is provided (+timer)
TrieResult TrieOperations::search_word(const string& word){
    Timer timer;
    timer.start();

    vector<string> results;
    // word: input, result: reference for output
    bool found = trie.search(word, results);

    long long time = timer.stop();

    // Create Comma, Seperating strings for different spanish iterations of english word
    stringstream ss;
    for (size_t i = 0; i < results.size(); i ++){
        ss << results[i];
        if (i < results.size() - 1) ss << ", ";
    }

    // Establish outputs for word found, translation, and timer results then return
    TrieResult output;
    output.found = found; // true or false
    output.translate = ss.str(); // result contains the translated words
    output.time = time; // time it took to search and find
    return output;
}