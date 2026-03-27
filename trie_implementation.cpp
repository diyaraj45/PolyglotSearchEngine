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

int main() {
    // Step 1: Load dataset
    vector<entry> dataset = loadDataset("data.csv");

    if (dataset.empty()) {
        cout << "Dataset failed to load or is empty." << endl;
        return 1;
    }

    cout << "\n--- DATASET LOADED SUCCESSFULLY ---" << endl;
    cout << "Total entries: " << dataset.size() << endl;

    // Step 2: Create TrieOperations object
    TrieOperations trieOps;

    // Step 3: Insert dataset into Trie and time it
    long long insertTime = trieOps.parser_trie(dataset);

    cout << "\n--- TRIE BUILD COMPLETE ---" << endl;
    cout << "Insertion time: " << insertTime << " ns" << endl;

    // Step 4: Test English -> Spanish searches
    cout << "\n--- TESTING ENGLISH TO SPANISH ---" << endl;

    vector<string> englishTests = {"Go.", "Hi.", "Run!"};

    for (size_t i = 0; i < englishTests.size(); i++) {
        TrieResult result = trieOps.search_word(englishTests[i]);

        cout << "\nSearch word: " << englishTests[i] << endl;
        if (result.found) {
            cout << "Translation(s): " << result.translate << endl;
            cout << "Search time: " << result.time << " ns" << endl;
        } else {
            cout << "Word not found." << endl;
            cout << "Search time: " << result.time << " ns" << endl;
        }
    }

    // Step 5: Test Spanish -> English searches
    cout << "\n--- TESTING SPANISH TO ENGLISH ---" << endl;

    vector<string> spanishTests = {"Ve.", "Vete.", "Hola.", "¡Corre!"};

    for (size_t i = 0; i < spanishTests.size(); i++) {
        TrieResult result = trieOps.search_word(spanishTests[i]);

        cout << "\nSearch word: " << spanishTests[i] << endl;
        if (result.found) {
            cout << "Translation(s): " << result.translate << endl;
            cout << "Search time: " << result.time << " ns" << endl;
        } else {
            cout << "Word not found." << endl;
            cout << "Search time: " << result.time << " ns" << endl;
        }
    }

    // Step 6: Test a word that should not exist
    cout << "\n--- TESTING WORD NOT IN DATASET ---" << endl;

    TrieResult missing = trieOps.search_word("Banana");

    cout << "\nSearch word: Banana" << endl;
    if (missing.found) {
        cout << "Translation(s): " << missing.translate << endl;
    } else {
        cout << "Word not found." << endl;
    }
    cout << "Search time: " << missing.time << " ns" << endl;

    cout << "\n--- TEST COMPLETE ---" << endl;

    return 0;
}