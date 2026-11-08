//Loaders.h: Declaration for functions that load from files - Nathan Moody
#ifndef LOADERS_H
#define LOADERS_H

#include <string>
#include <vector>

//loadBuildings(loads buildings by name from file into a vector)
void loadBuildings(std::vector<std::string>& b, const std::string& file);
//End

//loadFacilities(loads facilities from file)
void loadFacilities(std::vector<Facility>& facilities, HashTable& table, 
    const std::vector<std::string>& buildings, const std::string& file);
//End

#endif 