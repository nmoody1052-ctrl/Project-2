//Loaders.cpp: Functions that load from file - Nathan Moody
#include <iostream>
#include <vector>
#include "utility.h"
#include "loaders.h"
#include <fstream>
#include <string>
using namespace std;

// loadBuildings: loads buildings from a file into a vector, rejecting duplicates
void loadBuildings(vector<string>& b, const string& file) {
    int lineNum = 0;
    int numAccepted = 0;
    int numRejected = 0;
    string line;

    ifstream buildingFile(file);

    // Missing file: print error, treat as empty
    if (!buildingFile.is_open()) {
        cerr << "Error: cannot open " << file << ", treating as empty\n";
        cout << file << ": " << numAccepted << " accepted, " << numRejected << " rejected\n\n";
        return;
    }

    while (getline(buildingFile, line)) {
        lineNum++;
        line = trim(line);

        // Skip blank lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Check for a duplicate (ignoring case)
        bool duplicate = false;
        for (size_t i = 0; i < b.size(); i++) {
            if (checkEqual(b[i], line)) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cerr << "Warning: " << file << " line " << lineNum
                 << ": duplicate building \"" << line << "\"\n";
            numRejected++;
        } else {
            b.push_back(line);
            numAccepted++;
        }
    }

    cout << file << ": " << numAccepted << " accepted, " << numRejected << " rejected\n\n";
}
//End