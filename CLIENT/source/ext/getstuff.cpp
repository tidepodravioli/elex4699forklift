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

#include "../../headers/ext/getstuff.h"

using namespace std;

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
        if(input.size() == 1) 
        {
            * result = input[0];
            return true;
        }
        else return false;
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

bool raf_cin::prompt(std::string message, int &result, std::string errMessage, int maxRetry)
{
    std::cout << message;

    int attempts = 0;
    while(!get_int(&result))
    {
        attempts++;
        if(attempts == maxRetry) return false;
        std::cout << errMessage;
    }

    return true;
}

bool raf_cin::prompt(std::string message, float &result, std::string errMessage, int maxRetry)
{
    std::cout << message;

    int attempts = 0;
    while(!get_float(&result))
    {
        attempts++;
        if(attempts == maxRetry) return false;
        std::cout << errMessage;
    }

    return true;
}

bool raf_cin::prompt(std::string message, std::string &result, std::string errMessage, int maxRetry)
{
    std::cout << message;

    int attempts = 0;
    while(!get_line(&result))
    {
        attempts++;
        if(attempts >= maxRetry) return false;
        std::cout << errMessage;
    }

    return true;
}

bool raf_cin::prompt(std::string message, std::string &result, std::regex expression, std::string errMessage, int maxRetry)
{
    std::cout << message;

    int attempts = 0;
    while(!get_data(&result, expression))
    {
        attempts++;
        if(attempts >= maxRetry) return false;
        std::cout << errMessage;
    }

    return true;
}

bool raf_cin::prompt_yn(std::string message, std::string errMessage)
{
    std::cout << message << " (y/n) : ";

    std::string response;
    while(!get_data(&response, std::regex("^(Y|y|N|n)$")))
    {
        std::cout << ((errMessage == "") ? message : errMessage) << " (y/n) : ";
    }

    if(response == "y" || response == "Y") return true;
    else return false;
}

vector<string> raf_cin::delimitString(std::string input, char delimiter)
{
    vector<string> parts;
    string builder = "";
    for(int charPosition = 0; charPosition < input.size(); charPosition++)
    {
      if(charPosition == input.size() - 1)
        builder += input.at(charPosition); 

      if(input.at(charPosition) == delimiter || charPosition == input.size() - 1) 
      {
        parts.push_back(builder);
        builder = "";
      }
      else builder += input.at(charPosition);
    }

    return parts;
}