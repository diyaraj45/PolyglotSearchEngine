#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "parser.h"
using namespace std;


string parseFile(stringstream& ss) {
    string field;
    char c;
    ss.get(c);
    if (c == '"') {
        while (ss.get(c)) {
            if (c == '"') {
                if (ss.peek() == '"') {
                    ss.get(c);
                    field += '"';
                } else {
                    break; 
                }
            } else {
                field += c;
            }
        }
        if (ss.peek() == ',') ss.get(c);
    } else {
        field += c;
        while (ss.peek() != ',' && ss.peek() != EOF) {
            ss.get(c);
            field += c;
        }  
        if (ss.peek() == ',') ss.get(c); 
    }

    return field;
}

vector<entry> loadDataset(const string& filename) {
    vector<entry> entries;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return entries;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        entry entry;

        entry.english = parseFile(ss);
        entry.spanish.push_back(parseFile(ss));

        if (!entry.english.empty() && !entry.spanish.empty()) {
            entries.push_back(entry);
        }
    }
    file.close();
    cout << "Loaded " << entries.size() << " entries." << endl;
    return entries;
}

// //quick check to see if the parser works correctly (it does) - delete later!!!
// int main() {
//     vector<entry> dataset = loadDataset("data.csv");

//     for (int i = 0; i < 5 && i < dataset.size(); i++) {
//         cout << "EN: " << dataset[i].english << " | ES: ";
//         for (int j = 0; j < dataset[i].spanish.size(); j++) {
//         cout << dataset[i].spanish[j];
//         if (j < dataset[i].spanish.size() - 1) cout << ", ";
//         }
//         cout << endl;
//     }   

//     return 0;
// }