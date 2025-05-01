/**
 * @file getstuff.cpp
 * @author Rafael Banalan  A01367816 4S (abanalan@my.bcit.ca)
 * @brief Implementation of getstuff.h
 * @version 0.1
 * @date 2025-01-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "getstuff.h"

bool raf_cin::get_int(int * result)
{
    std::string input;
    if(get_data(&input, std::regex(INTEGER_REGEX)))
    {
        try
        {
            * result = std::stoi(input);
            return true;
        }
        catch(const std::exception& exception)
        {
            return false;
        }
    }

    return false;
}

bool raf_cin::get_float(float * result)
{
    std::string input;
    if(get_data(&input, std::regex(FLOAT_REGEX)))
    {
        try
        {
            * result = std::stof(input);
            return true;        }
        catch(const std::exception& exception)
        {
            return false;
        }
    }

    return false;
}

bool raf_cin::get_char(char * result)
{
    std::string input;
    if(get_data(&input, std::regex(CHAR_REGEX)))
    {
        * result = input[0];
        return true;
    }
    return false;
}

bool raf_cin::get_line(std::string * result)
{
    std::getline(std::cin, * result);
    return !std::cin.fail();
}

bool raf_cin::get_data(std::string * result, std::regex data)
{
    if(get_line(result)){
        return(std::regex_match(* result, data));
    }
    else return false;
}