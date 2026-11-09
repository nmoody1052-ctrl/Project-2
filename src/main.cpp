//Main.cpp: makes everything actually work - Nathan Moody, Mahamat 
//Include
#include <iostream>
#include <fstream>
#include <vector>

#include "loaders.h"
#include "facility.h"
#include"hashtable.h"
#include "utility.h"
#include "facilityops.h"
using namespace std;

//Prints Header
void header(){
        cout<<
        "+-----------------------------------------------+\n"<<
        "|        Computer Science and Engieering        |\n"<<
        "|          CSCE 2110 - Data Structures          |\n"<<
        "|                                               |\n"<<
        "|                    Mahamat                    |\n"<<
        "|              Nathan Moody NJM0184             |\n"<<
        "+-----------------------------------------------+\n\n";
}
//End

//Prints Menu
void menu(){
        cout<<
        "*********************** Menu **********************\n"<<
        "| 1. View all Facilities                           |\n"<<
        "| 2. Search Facility by ID                         |\n"<<
        "| 3. View Campus Graph                             |\n"<<
        "| 4. Display Graph Counts and Degrees              |\n"<<
        "| 5. Find Reachable Buildings (BFS                 |\n"<<
        "| 6. Add Department                                |\n"<<
        "| 7. Search Department                             |\n"<<
        "| 8. Display Department Hierarchy                  |\n"<<
        "| 9. Run Preorder Traversal                        |\n"<<
        "| 10. Exit                                         |\n"<<
        "***************************************************\n"<<
        ">> ";
}
//End

//Main
int main(int argc, char* argv[]) {
    string dataDir = (argc > 1) ? argv[1] : "data";
    vector<string> buildings;
    vector<Facility> facilities;
    HashTable table;

    // Load in the required order
    loadBuildings(buildings, dataDir + "/buildings.txt");
    // loadConnections(...);       // TODO: partner
    loadFacilities(facilities, table, buildings, dataDir + "/facilities.txt");
    // loadDepartments(...);       // TODO: partner

    int choice = -1;
    while (choice != 0) {
        menu();
        choice = readMenuChoice(9);
        switch (choice) {
            case 1: displayFacilities(facilities); break;
            case 2: searchFacilityById(table); break;
            case 3: case 4: case 5: case 6: case 7: case 8: case 9:
                cout << "(not connected yet)\n";   // TODO: partner's functions go here
                break;
            case 0: cout << "Goodbye.\n"; break;
            default: cout << "Invalid choice. Enter a number from 0 to 9.\n";
        }
    }
    return 0;
}