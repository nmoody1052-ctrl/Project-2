//utility.cpp: Utility functions definitions for strings, comparing, uppercase, lowercase, and triming whitespace - Nathan Moody
#include <iostream>
#include <string>
#include <cctype>
#include "utility.h"
using namespace std;
    //trim (removes whitespace {space, tab, \r, \n})
    string trim(const string& s) {
        size_t first = s.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            return "";
        }
        size_t last = s.find_last_not_of(" \t\r\n");
        return s.substr(first, last - first + 1);
    }
    //End

    //toUpper: returns an uppercase copy of s
    string toUpper(const string& s) {
        string result;
        for (size_t i = 0; i < s.length(); i++) {
            result += toupper(static_cast<unsigned char>(s[i]));
        }
        return result;
    }
    //End

    //toLower (Lowercases a string)
    string toLower(const string& s) {
        string result;
        for (size_t i = 0; i < s.length(); i++) {
            result += tolower(static_cast<unsigned char>(s[i]));
        }
        return result;
    }
    //End

    //checkEqual (checks if strings are equal {ignores case})
    bool checkEqual(const string& a, const string& b){
        return toLower(a) == toLower(b);
    }
    //End

    //Splits a list (thingA|thingB|ThingC) into seperate strings [DELIM IS THE CHAR SEPERATING THE THINGS, FOR EXAMPLE '|' ]
    vector<string> splitFields(const string& line, char delim){
        vector<string> fields;
        string current;

        //Split on each delim
        for(size_t i=0; i<line.length();i++){
            if(line[i]==delim){
                fields.push_back(trim(current));
                current.clear();
            }
            else{
                current += line[i];
            }
        }
        //End

        fields.push_back(trim(current));
        return fields;
    }
    //End

    //isValidFacilityId: true if id is 'F' followed by exactly 3 digits
    bool isValidFacilityId(const string& id) {
        if (id.length() != 4 || id[0] != 'F'){
            return false;
        }
        for (size_t i = 1; i < id.length(); i++) {
            if (!isdigit(static_cast<unsigned char>(id[i]))){
                return false;
            }
        }
        return true;
    }
    //End

    //Shows input prompt, reads a whole line, returns it trimmed
    string promptLine(const string& prompt) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            return ""; 
        }
        return trim(line);
    }
    //End

    //Reads Menu Chouce
    int readMenuChoice(int maxChoice) {
        string line = promptLine("Enter choice: ");
        if (line.empty()) {
            if(cin.eof()){
               return 0; 
            }
            else{
                return 1;
            }
        }
        if (line.length() > 3){
            return -1;
        }
        for (size_t i =0; i<line.length(); i++) {
            if (!isdigit(static_cast<unsigned char>(line[i]))){
                return -1;
            }
        }
        int n = stoi(line);
        if (n > maxChoice){
            return -1;
        }
        else{
            return n;
        }
    }
    //End