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
    entriesNumber = 0;
}

int hashTable::hashFunction(const string& key) {
    int hashValue = 0;
    for (char c : key) {
        hashValue = (hashValue * 31 + c) % table.size();
    }
    return hashValue % table.size();
}

void hashTable::insert(const entry& e) {
    int index = hashFunction(e.english);
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
}

entry* hashTable::search(const string& key) {
    int index = hashFunction(key);
    for (auto& existingEntry : table[index]) {
        if (existingEntry.english == key) {
            return &existingEntry;
        }
    }
    return nullptr;
}