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
        unsigned char c = (unsigned char)word[i];
        if (c >= 128) {
            cleanWord += c; 
        } else if (isalnum(c)) {
            cleanWord += (char)tolower(c);
        }
    }
    return cleanWord;
}

int main() {
    //load data from data.scv file
    vector<entry> dataset = loadDataset("data.csv");

    for (int i = 0; i < dataset.size(); i++) {
        dataset[i].english = normalizeWord(dataset[i].english);
        for (int j = 0; j < dataset[i].spanish.size(); j++) {
            dataset[i].spanish[j] = normalizeWord(dataset[i].spanish[j]);
        }
    }

    vector<entry> reverseDataset;
    for (int i = 0; i < dataset.size(); i++) {
        for (int j = 0; j < dataset[i].spanish.size(); j++) {
            entry reverseEntry;
            reverseEntry.english = dataset[i].spanish[j];
            reverseEntry.spanish.push_back(dataset[i].english);
            reverseDataset.push_back(reverseEntry);
        }
    }

    cout << "normalized dataset loaded." << endl;

    //build trie
    TrieOperations trieOps;
    long long trieBuildTime = trieOps.parser_trie(dataset);
    TrieOperations reverseTrieOps;
    long long reverseTrieBuildTime = reverseTrieOps.parser_trie(reverseDataset);

    //build hash table
    hashTable hash(dataset.size());

    Timer hashBuildTimer;
    hashBuildTimer.start();
    for (int i = 0; i < dataset.size(); i++) {
        hash.insert(dataset[i]);
    }

    long long hashBuildTime = hashBuildTimer.stop();
    cout << "Hash table build time: " << hashBuildTime << " ns" << endl;

    //user input
    string word;
    cout << "Enter a word to search: " << flush;
    cin >> word;
    word = normalizeWord(word);
    string direction;
    cout << "Enter search direction (english_to_spanish or spanish_to_english): " << flush;
    cin >> direction;

    //Trie Search
    // TrieResult trieOutput = trieOps.search_word(word);
    // string trieResult = "Word not found";
    // long long trieTime = trieOutput.time;
    // if (trieOutput.found) {
    //     trieResult = trieOutput.translate;
    // }

    string trieResult = "Word not found";
    long long trieTime = 0;
    if (direction == "english_to_spanish") {
        TrieResult trieOutput = trieOps.search_word(word);
        trieTime = trieOutput.time;
        if (trieOutput.found) {
            trieResult = trieOutput.translate;
        }
    } else if (direction == "spanish_to_english") {
        TrieResult trieOutput = reverseTrieOps.search_word(word);
        trieTime = trieOutput.time;
        if (trieOutput.found) {
            trieResult = trieOutput.translate;
        }
    }

    //Hash Search
    string hashResult = "Word not found";
    entry* hashEntry = nullptr;
    long long totalHashTime = 0;
    int hashRuns = 0;
    const long long minimumTotalTime = 1000000; // 1 millisecond in nanoseconds

    do {
        Timer hashSearchTimer;
        hashSearchTimer.start();

        if (direction == "english_to_spanish") {
            hashEntry = hash.search(word);
        } 
        else if (direction == "spanish_to_english") {
            hashEntry = hash.searchSpanish(word);
        }
        totalHashTime += hashSearchTimer.stop();
        hashRuns++;

    } while (totalHashTime < minimumTotalTime); 
    long long hashTime = totalHashTime / hashRuns; //average time per search

    //check if the hash table found the word
    if (hashEntry != nullptr) { 
        entry& foundEntry = *hashEntry; //pointer into normal reference.
        if (direction == "english_to_spanish") { //check if we are searching in the english_to_spanish direction
            if (!foundEntry.spanish.empty()) {
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
    else if (direction == "spanish_to_english") { //check if we are searching in the spanish_to_english direction
        hashResult = foundEntry.english;
    }
}

    //Print results
    cout << "Word: " << word << endl;
    cout << "TrieResult: " << trieResult << endl;
    cout << "TrieTime: " << trieTime << " ns" << endl;
    cout << "HashResult: " << hashResult << endl;
    cout << "HashTime: " << hashTime << " ns" << endl;

}