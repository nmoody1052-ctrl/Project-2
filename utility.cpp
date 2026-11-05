//Utility functions 
#include <string>
#include <cctype>
#include "utility.h"
using namespace std;
    //Trim (Trims whitespace off of a string)
    string trim(const string& s){
        
    }
    //End

    // toUpper: returns an uppercase copy of s
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

    //equal(checks if strings are equal if we ignore case
    bool checkEqual(const string& a, const string& b){
        return toLower(a) == toLower(b);
    }
    //End