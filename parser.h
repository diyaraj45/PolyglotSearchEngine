#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct entry {
    string english;
    string spanish;
};

vector<entry> parseFile(const string& filename);
