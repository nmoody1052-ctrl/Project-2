// main
#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "utility.h"
#include <fstream>
#include <iostream>
using namespace std;

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


