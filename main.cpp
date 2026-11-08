//Main.cpp: makes everything actually work - Nathan Moody, Mahamat 
//Include
#include <iostream>
#include <fstream>
#include <vector>
//End

//Including Headers
#include "loaders.h"
#include "utility.h"
//End

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