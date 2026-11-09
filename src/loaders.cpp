//Loaders.cpp: Functions that load from file - Nathan Moody
#include <iostream>
#include <vector>
#include "utility.h"
#include "loaders.h"
#include "facility.h"
#include "hashtable.h"
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
    //End

    while (getline(buildingFile, line)) {
        lineNum++;
        line = trim(line);

        // Skip blank lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        //End

        // Check for a duplicate (ignoring case)
        bool duplicate = false;
        for (size_t i = 0; i < b.size(); i++) {
            if (checkEqual(b[i], line)) {
                duplicate = true;
                break;
            }
        }
        //End

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

// loadFacilities: loads facilities.txt, validates each record, stores accepted ones in file order (facilities) and in the hash table (table)
void loadFacilities(vector<Facility>& facilities, HashTable& table,
                    const vector<string>& buildings, const string& file) {
    int lineNum = 0;
    int numAccepted = 0;
    int numRejected = 0;
    string line;

    ifstream facilityFile(file);

    // Missing file: print error, treat as empty
    if (!facilityFile.is_open()) {
        cerr << "Error: cannot open " << file << ", treating as empty\n";
        cout << file << ": 0 accepted, 0 rejected (hash capacity "
             << table.getCapacity() << ", entries " << table.getEntries()
             << ", collisions " << table.getCollisions() << ")\n\n";
        return;
    }
    //End

    while (getline(facilityFile, line)) {
        lineNum++;
        line = trim(line);

        // Skip blank lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        //End

        // Check field count
        vector<string> fields = splitFields(line, '|');
        if (fields.size() != 4) {
            cerr << "Warning: " << file << " line " << lineNum
                 << ": wrong field count (expected 4, got " << fields.size() << ")\n";
            numRejected++;
            continue;
        }
        //End

        // Check for empty fields
        if (fields[0].empty() || fields[1].empty() || fields[2].empty() || fields[3].empty()) {
            cerr << "Warning: " << file << " line " << lineNum << ": empty field\n";
            numRejected++;
            continue;
        }
        //End

        // Normalize ID, then validate format: F + exactly 3 digits
        string id = toUpper(fields[0]);
        bool validId = (id.length() == 4 && id[0] == 'F');
        for (size_t i = 1; validId && i < id.length(); i++) {
            if (!isdigit(static_cast<unsigned char>(id[i]))) {
                validId = false;
            }
        }
        if (!validId) {
            cerr << "Warning: " << file << " line " << lineNum
                 << ": invalid ID \"" << fields[0] << "\" (must be F plus exactly 3 digits)\n";
            numRejected++;
            continue;
        }
        //End

        // Building must exist; use the spelling from buildings.txt
        string buildingName;
        bool foundBuilding = false;
        for (size_t i = 0; i < buildings.size(); i++) {
            if (checkEqual(buildings[i], fields[2])) {
                buildingName = buildings[i];
                foundBuilding = true;
                break;
            }
        }
        if (!foundBuilding) {
            cerr << "Warning: " << file << " line " << lineNum
                 << ": unknown building \"" << fields[2] << "\"\n";
            numRejected++;
            continue;
        }
        //End

        // Build the facility and try inserting into the hash table
        Facility f;
        f.id = id;
        f.name = fields[1];
        f.building = buildingName;
        f.category = fields[3];

        if (!table.insert(f)) {
            cerr << "Warning: " << file << " line " << lineNum
                 << ": duplicate ID " << id << "\n";
            numRejected++;
            continue;
        }
        //End

        // Accepted: keep in file orxer
        facilities.push_back(f);
        numAccepted++;
        //End
    }

    cout << file << ": " << numAccepted << " accepted, " << numRejected
         << " rejected (hash capacity " << table.getCapacity()
         << ", entries " << table.getEntries()
         << ", collisions " << table.getCollisions() << ")\n\n";
}
//End