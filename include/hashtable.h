//Hashtable.h: defines functions for custom hash table for facilities - Nathan Moody
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include "facility.h"

const int defCapacity = 11;

class HashTable{
    private:
        //
        int hashFunction(const std::string& key) const;
        //End

        //Vector Declaration
        std::vector<std::vector<Facility>> table;
        //End

        //Vars
        int capacity;
        int entries;
        int collisions;
        //End
    public:
        //Constructor
        HashTable(int cap = defCapacity);
        //End

        //Inserts, returns false if duplicate
        bool insert(const Facility& f);
        //End

        //Find facility, return nullptr if not found
        const Facility* find(const std::string& id) const;
        //End

        //Getters
        int getCapacity() const;

        int getEntries() const;
        
        int getCollisions() const;
        //End
};

#endif