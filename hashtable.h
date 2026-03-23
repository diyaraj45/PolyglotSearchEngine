#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "parser.h"
using namespace std;

class hashTable {
    private:
        vector<vector<entry>> table;
        int entriesNumber;
        int hashFunction(const string& key);

    public:
        hashTable(int s);
        void insert(const entry& e);
        entry* search(const string& key);
};