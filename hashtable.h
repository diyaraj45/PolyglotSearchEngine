#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "parser.h"
#pragma once
using namespace std;

class hashTable {
    private:
        vector<vector<entry>> table;
        vector<vector<entry>> spanishTable;
        int entriesNumber;
        int hashFunction(const string& key, int tablesize);

    public:
        hashTable(int s);
        void insert(const entry& e);
        entry* search(const string& key);
        entry* searchSpanish(const string& key);
};