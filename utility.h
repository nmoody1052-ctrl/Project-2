//Utility functions declarations for strings, comparing, uppercase, lowercase, and triming whitespace - Nathan Moody
#ifndef UTILITY_H
#define UTILITY_H
#include <string>

//Trim (Trims whitespace off of a string)
std::string trim(const std::string& s);
//End

//toUpper (Uppercases a string)
std::string toUpper(const std::string& s);
//End

//toLower (Lowercases a string)
std::string toLower(const std::string& s);
//End

//checkEqual (checks if strings are equal {ignores case})
bool checkEqual(const std::string& a, const std::string& b);
//End

#endif