//Hashtable.cpp: implementation of custom facilty hash table - Nathan Moody
#include <iostream>
#include <vector>
#include <string>
#include "hashtable.h"
#include "utility.h"
using namespace std;

    // hashFunction: turns an uppercase facility ID into a bucket index (0 to capacity - 1)
    int HashTable::hashFunction(const string& key) const {
        unsigned long hash = 0;
        for (char c : key) {
            hash = hash * 31 + static_cast<unsigned char>(c);
        }
        return static_cast<int>(hash % capacity);
    }
    //End

    //Constructor
    HashTable::HashTable(int cap){
        capacity = cap;
        entries = 0;
        collisions = 0;
        table.resize(capacity);
    }
    //End

    //Inserts, returns false if duplicate
    bool HashTable::insert(const Facility& f){
        Facility copy = f;
        copy.id = toUpper(trim(f.id));
        int index = hashFunction(copy.id);

        //Checks if table is a duplicate and returns false + doesn't add if it is
        for(size_t i=0;i<table[index].size();i++){
            if(table[index][i].id==copy.id){
                return false;
            }
        }
        //End

        //If the table is not empty increments collision
        if (!table[index].empty()){
            collisions++;
        }
        //End

        //Adds table and increments entries
        table[index].push_back(copy);
        entries++;
        //End

        return true;
    }
    //End

    //Find facility, return nullptr if not found
    const Facility* HashTable::find(const string& id) const{
        //Normalize the ID (trim + uppercase), then compute its bucket
        string key = toUpper(trim(id));
        int index = hashFunction(key);
        //End

        //Returns table if found
        for(size_t i=0;i<table[index].size();i++){
            if(table[index][i].id==key){
                return &table[index][i];
            }
        }
        //End

        return nullptr;
    }
    //End

    //Getters
    int HashTable::getCapacity() const{
        return capacity;
    }

    int HashTable::getEntries() const{
        return entries;
    }
        
    int HashTable::getCollisions() const{
        return collisions;
    }
    //End
