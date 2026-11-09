// facilityops.cpp: implementations of menu operations for facilities, the search uses the custom hash table - Nathan Moody
#include <iostream>
#include "facilityops.h"
#include "utility.h"
using namespace std;

//Displays all facilites and the total number
void displayFacilities(const vector<Facility>& facilities) {
    if (facilities.empty()) {
        cout <<"No facilities are loaded.\n";
        return;
    }
    for(size_t i=0; i<facilities.size(); i++) {
        cout <<facilities[i].id <<" | "<< facilities[i].name<<" | "<<facilities[i].building <<" | "<<facilities[i].category<<"\n";
    }
    cout <<"Total facilities: "<<facilities.size()<<"\n";
}
//End

// searchFacilityById: looks up an ID using the hash table
void searchFacilityById(const HashTable& table) {
    string input = promptLine("Enter facility ID: ");
    if(input.empty()) {
        cout<<"Error: ID cannot be blank.\n";
        return;
    }
    string id = toUpper(input);
    if (!isValidFacilityId(id)) {
        cout<<"Invalid format: an ID is F followed by exactly three digits.\n";
        return;
    }
    const Facility* f = table.find(id);
    if (f == nullptr) {
        cout<<"Not found: no facility with ID "<<id<<"\n";
    } else {
        cout<<"Found: "<<f->name<<" | "<<f->building<<" | "<<f->category<<"\n";
    }
}
//End