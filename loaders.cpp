//Functions that load from file
#include <iostream>
#include <vector>
#include "utility.h"
#include <fstream>
#include <string>
using namespace std;

//loadBuildings loads buildings from a file into a vector
void loadBuildings(vector<string> b, const string& file){
    //Opens File
    ifstream buildingFile(file);
    //End

    //Checks if file opened properly, returns error if not
    if (!buildingFile.is_open()) {
        cerr << "Unable to open " << file << "\n";
        return;
    }
    //End


}
//End