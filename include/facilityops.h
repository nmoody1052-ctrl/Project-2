//facilityOps: Menu operations for facilities, the search uses the custom hash table- Nathan Moody
#ifndef FACILITYOPS_H
#define FACILITYOPS_H
#include <vector>
#include "facility.h"
#include "hashtable.h"

//Displays all facilites
void displayFacilities(const std::vector<Facility>& facilities);
//End

//Searches for facility via ID
void searchFacilityById(const HashTable& table);
//End

#endif