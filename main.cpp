//Main.cpp: makes everything actually work - Nathan Moody, Mahamat 
//Include
#include <iostream>
#include <fstream>
#include <vector>

#include "loaders.h"
#include "facility.h"
#include"hashtable.h"
#include "campusgraph(1).h"
#include "departmenttree(1).h"
#include "utility.h"
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

// main
int main() {
    CampusGraph g;
    // Stand-in for the teammate's building loader.
    ifstream b("buildings.txt");
    string line;
    while (getline(b, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        g.addBuilding(line);
    }
    int c = g.loadConnections("connections.txt");
    cout << "Loaded " << c << " connections\n\n";
    g.displayGraph();
    cout << "\n";
    g.displayStatistics();
    cout << "\n";
    g.bfsReachability("library");
    cout << "\n";
    g.bfsReachability("Observatory");
    cout << "\n";
    g.bfsReachability("Nowhere Hall");
    cout << "\n";
    g.shortestPath("Library", "Engineering Building");
    cout << "\n";
    g.shortestPath("Gym", "Gym");
    cout << "\n";
    g.shortestPath("Library", "Observatory");
    cout << "\n";

    DepartmentTree t;
    int d = t.loadFromFile("departments.txt");
    cout << "Loaded " << d << " departments\n\n";
    t.displayHierarchy();
    cout << "\n";
    t.displayPreorder(); t.displayPostorder(); t.displayLevelOrder();
    cout << "\n";
    t.displayStatistics();
    cout << "\n";
    t.searchDepartment("computer science");
    cout << "\n";
    t.searchDepartment("UNIVERSITY");
    cout << "\n";
    t.searchDepartment("Biology");
    cout << "\n";
    promptAddDepartment(t);   // read
    promptAddDepartment(t);
    promptAddDepartment(t);
    t.displayHierarchy();
    DepartmentTree empty;
    cout << "\n";
    empty.displayHierarchy(); empty.displayStatistics();
    promptAddDepartment(empty);
    empty.displayStatistics();
    return 0;
}
