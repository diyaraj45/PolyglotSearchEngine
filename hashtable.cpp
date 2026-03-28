#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "parser.h"
#include "hashtable.h"
using namespace std;

hashTable::hashTable(int s) {
    table.resize(s);
    spanishTable.resize(s);
    entriesNumber = 0;
}

int hashTable::hashFunction(const string& key, int tablesize) {
    int hashValue = 0;
    for (char c : key) {
        hashValue = (hashValue * 31 + c) % tablesize;
    }
    return hashValue % tablesize;
}

void hashTable::insert(const entry& e) {
    int index = hashFunction(e.english, table.size());
    if (table[index].empty()) {
        table[index].push_back(e);
        entriesNumber++;
    } else {
        for (auto& existingEntry : table[index]) {
            if (existingEntry.english == e.english) {
                existingEntry.spanish.push_back(e.spanish[0]);
                return;
            }
        }
        table[index].push_back(e);
        entriesNumber++;
    }

    for (const string& spanishWord : e.spanish) {
        int spanishIndex = hashFunction(spanishWord, spanishTable.size());
        if (spanishTable[spanishIndex].empty()) {
            spanishTable[spanishIndex].push_back(e);
        } else {
            bool found = false;
            for (auto& existingEntry : spanishTable[spanishIndex]) {
                if (existingEntry.spanish[0] == spanishWord) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                spanishTable[spanishIndex].push_back(e);
            }
        }
    }
}

entry* hashTable::search(const string& key) {
    int index = hashFunction(key, table.size());
    for (auto& existingEntry : table[index]) {
        if (existingEntry.english == key) {
            return &existingEntry;
        }
    }
    return nullptr;
}

entry* hashTable::searchSpanish(const string& key) {
    int index = hashFunction(key, spanishTable.size());
    for (auto& existingEntry : spanishTable[index]) {
        for (const string& spanishWord : existingEntry.spanish) {
            if (spanishWord == key) {
                return &existingEntry;
            }
        }
    }
    return nullptr;
}