#include <iostream> 
#include <string>
#include <vector>
#include <cctype>
#include <chrono>
#include "parser.h"
#include "hashtable.h"
#include "trie_implementation.h"
#include "timer.h"
using namespace std;


string normalizeWord(string word) {
    string cleanWord = "";
    for (int i = 0; i < word.size(); i++) {
        char c = word[i];
        if (isalnum(c)) {
            cleanWord += tolower(c);
        }
    }
    return cleanWord;
}

int main() {
    //load data from data.scv file
    vector<entry> dataset = loadDataset("data.csv");

    for (int i = 0; i < dataset.size(); i++) {
        dataset[i].english = normalizeWord(dataset[i].english);
    }

    //build trie
    TrieOperations trieOps;
    long long trieBuildTime = trieOps.parser_trie(dataset);

    //build hash table
    hashTable hash(dataset.size());

    Timer hashBuildTimer;
    hashBuildTimer.start();
    for (int i = 0; i < dataset.size(); i++) {
        hash.insert(dataset[i]);
    }

    long long hashBuildTime = hashBuildTimer.stop();

    //user input
    string word;
    cout << "Enter a word to search: ";
    cin >> word;
    word = normalizeWord(word);

    //Trie Search
    TrieResult trieOutput = trieOps.search_word(word);
    string trieResult = "Word not found";
    long long trieTime = trieOutput.time;
    if (trieOutput.found) {
        trieResult = trieOutput.translate;
    }

    //Hash Search
    string hashResult = "Word not found";
    entry* hashEntry = nullptr;
    long long hashTime = 0;
    int hashRuns = 0;

    Timer hashSearchTimer;
    hashSearchTimer.start();

    do {
        hashEntry = hash.search(word);
        hashRuns++;
        hashTime = hashSearchTimer.stop();
    } while (hashTime == 0); //keep searching until we get a valid time (handles edge case of very fast searches)
    hashTime = hashTime / hashRuns; //average time per search
    //check if the hash table found the word
    if (hashEntry != nullptr) {
        entry& foundEntry = *hashEntry; //pointer into normal reference.
        if (!foundEntry.spanish.empty()) { //check for at least one translation
            string resultText = ""; //store all translations as one string. 
            for (int i = 0; i < foundEntry.spanish.size(); i++) {
                resultText += foundEntry.spanish[i];
                if (i < foundEntry.spanish.size() - 1) { //add comma if not the last translation
                    resultText += ", ";
                }
            }
            hashResult = resultText;
        }
    }

    //Print results
    cout << "Word: " << word << endl;
    cout << "TrieResult: " << trieResult << endl;
    cout << "TrieTime: " << trieTime << " ns" << endl;
    cout << "HashResult: " << hashResult << endl;
    cout << "HashTime: " << hashTime << " ns" << endl;

}