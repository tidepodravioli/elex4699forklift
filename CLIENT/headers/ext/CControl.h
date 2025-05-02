 /**
 * @file CControl.h
 * @author Rafael Banalan  A01367816 4S (abanalan@my.bcit.ca)
 * @brief Represents a serial interface between the computer and a microcontroller.
 * @version 0.1
 * @date 2025-01-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "Serial.h"
#include "CJoystickPosition.hpp"
#include "../../../shared/headers/ext/CControlTypes.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>


/**
 * @brief Represents a serial interface between the computer and a microcontroller.
 * 
 */
class CControl {
protected:
    /**
     * @brief Serial object (part of Serial library) that communicates with the microcontroller over a COM port.
     * 
     */
    Serial m_com;
    bool m_flagPortOpen = false;

    /**
     * @brief Splits input string into a substrings based on a given delimiter
     * 
     * @param input String to be split
     * @param delimiter Character to split substrings at
     * @return vector<string> Vector of type string with all of the substrings
     */
    vector<string> delimitString(std::string input, char delimiter);
    /**
     * @brief Builds a ready-to-send command to send to the microcontroller
     * 
     * @param command The type of command to send (GET, SET, or ACK)
     * @param datatype The type of data wanted
     * @param channel The destination channel to write to
     * @param addEndl Whether or not to add a line feed character to the end of the command string
     * @param val The value to be sent, -1 if sending a GET
     * @return string 
     */
    string commandBuilder(COMMAND_TYPE command, DATA_TYPE datatype, int channel, bool addEndl = true, int val = -1);
    /**
     * @brief Reads a message off of the serial port and truncates the buffer so only the actual message is returned.
     * 
     * @param result The string object to return the message to
     * @return true if the message was successfully received
     * @return false otherwise
     */
    bool readMessage(string &result);

    /**
     * @brief Stores all of the times since each button was inactive
     * 
     */
    std::chrono::time_point<std::chrono::steady_clock> m_lastDebounceTimes[BUTTON_NUM_OF_CHANNELS];
    
    /**
     * @brief Stores a bool for each button representing whether a button was just recently pressed or not
     * 
     */
    bool m_buttonActive[BUTTON_NUM_OF_CHANNELS];

public:
    /**
     * @brief Construct a new CControl object
     * 
     */
    CControl();
    /**
     * @brief Destroys the CControl object
     * 
     */
    ~CControl();

    /**
     * @brief Initializes the connection to the microcontroller on the given COM port.
     * 
     * @param comport The number of the COM port (ex. COM*)
     */
    void init_com(int comport);

    /**
     * @brief Gets data of the given type from the microcontroller.
     * 
     * @param type The type of data to get
     * @param channel The channel to get the data from
     * @param result Where to store the value
     * @return true if communication was successful, data was retrieved, and acknowledgement received.
     * @return false otherwise
     */
    virtual bool get_data (DATA_TYPE type, int channel, int &result);

    /**
     * @brief Sets/writes data of the given type to the microcontroller.
     * 
     * @param type The type of data that is being sent
     * @param channel The channel to get write the data to
     * @param val The data being written
     * @return true if communication was successful, data written, and acknowledgement received.
     * @return false otherwise
     */
    virtual bool set_data (DATA_TYPE type, int channel, int val);

    /**
     * @brief Gets the position of the joystick(analog stick) as a raw ADC value
     * 
     * @param pass where to store a boolean of whether or not the serial communication was successful
     * @return CJoystickPosition 
     */
    CJoystickPosition get_analog(bool &pass);

    /**
     * @brief Checks if a button press was detected on SW1 on the microcontroller
     * 
     * @param pass where to store a boolean of whether or not the serial communication was successful
     * @return true if the button was pressed
     * @return false if the button wasn't pressed
     */
    bool get_button(int channel);

    /**
     * @brief Finds and connects to the first serial port that responds with an acknowledge message
     * 
     * @return true if a port was found
     * @return false if a port was not found
     */
    bool findPort();

    /**
     * @brief Sends a "check if alive" message to the presently connected serial port 
     * 
     * @return true if the microcontroller responded
     * @return false if no response was heard
     */
    bool checkPort();
};
