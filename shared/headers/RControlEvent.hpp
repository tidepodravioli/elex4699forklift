#pragma once

#include "ext/CControlTypes.h"
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>

/**
 * @brief Type of command being sent/received
 * 
 */
enum EVENT_COMMAND_TYPE {ECOMMAND_INVALID = -1, ECOMMAND_GET, ECOMMAND_SET, ECOMMAND_ACK};
/**
 * @brief Type of data being sent/received
 * 
 */
enum EVENT_DATA_TYPE {ETYPE_INVALID = -1, ETYPE_DIGITAL, ETYPE_ANALOG, ETYPE_COMMAND}; 

using namespace std;

/**
 * @brief Represents a packet sent over TCP/IP using Craig's CServer/CClient architechture
 * @details RControlEvent is a container for initializing and simplifying the construction and
 * implementation of commands sent over TCP between the server and client.
 */
class RControlEvent
{
    private:
    /**
     * @brief Builds a ready-to-send command to send to the microcontroller
     *
     * @param command The type of command to send (GET, SET, or ACK)
     * @param datatype The type of data wanted
     * @param channel The destination channel to write to
     * @param addEndl Whether or not to add a line feed character to the end of the command string
     * @param vals The value to be sent, blank if sending a GET
     * @return string
     */
    string commandBuilder(EVENT_COMMAND_TYPE command, EVENT_DATA_TYPE datatype, int channel, vector<string> vals = {}, bool addEndl = true);

    static vector<string> delimitString(string input, char delimiter);
    static EVENT_COMMAND_TYPE str_to_com(char com);
    static EVENT_DATA_TYPE str_to_type(string type);

    protected:
    EVENT_COMMAND_TYPE m_com;
    EVENT_DATA_TYPE m_type;
    int m_origin;
    vector<string> m_data;

    public:
    RControlEvent();
    RControlEvent(EVENT_COMMAND_TYPE com, EVENT_DATA_TYPE type, int origin, int value = -1);
    RControlEvent(EVENT_COMMAND_TYPE com, EVENT_DATA_TYPE type, int origin, vector<int> values = {});
    RControlEvent(EVENT_COMMAND_TYPE com, EVENT_DATA_TYPE type, int origin, vector<string> values = {});

    /**
     * @brief Returns the kind of command (GET, SET, ACK) this packet represents
     * 
     * @return EVENT_COMMAND_TYPE 
     */
    EVENT_COMMAND_TYPE getCom();

    /**
     * @brief Returns the type of data this packet contains
     * 
     * @return EVENT_DATA_TYPE 
     */
    EVENT_DATA_TYPE getType();

    /**
     * @brief Returns the channel that the data is from/meant for
     * 
     * @return int 
     */
    int getOrigin();

    /**
     * @brief Returns the first value of the packet as an integer
     * 
     * @return int The first value as an integer, -1 if invalid
     */
    int getValue();

    /**
     * @brief Returns the full, raw data of the packet as a vector of delimited strings
     * 
     * @return vector<string> 
     */
    vector<string> getValues();

    /**
     * @brief Returns the packet as a sendable command for transmission
     * 
     * @return string 
     */
    string asCommand(bool newline = false);

    static RControlEvent parse(string command);
};