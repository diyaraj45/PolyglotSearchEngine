#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct entry {
    string english;
    vector<string> spanish;
};

string parseFile(stringstream& ss);

vector<entry> loadDataset(const string& filename);
