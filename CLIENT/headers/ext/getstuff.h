/**
 * @file getstuff.h
 * @author Rafael Banalan  A01367816 4S (abanalan@my.bcit.ca)
 * @brief Functions that retrieve user input with error checking.
 *        Functions here return a true if the data in the result is valid,
 *        false otherwise.
 * @version 0.1
 * @date 2025-01-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <regex>
#include <string>

//default regex options for get_XXXXX() functions
#define TO_LOWERCASE 32
#define CHAR_REGEX "^.$"
#define INTEGER_REGEX "^[0-9]+$"
#define FLOAT_REGEX "^[0-9]+(|\\.|\\.([0-9]{1,2}))$"
#define NON_BLANK_STRING_REGEX "^[^\\s]+[a-zA-Z0-9 ]+$"

namespace raf_cin
{
    bool get_int(int * result); //gets an integer from user input
    bool get_float(float * result); //gets a float from user input
    bool get_char(char * result); //returns the first character of the user input if only one character was inputted

    bool get_line(std::string * result); //a wrapper for cin.getline() that returns the inverse of the cin.fail() flag
    bool get_data(std::string * result, std::regex data); //gets a line of user input and checks it against a regex
}
