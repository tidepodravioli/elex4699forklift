#pragma once

#include "RNetServer.hpp"

#define COM_GET_CHAR "G" ///< Character representing a GET command on the serial bus
#define COM_SET_CHAR "S"///< Character representing a SET command on the serial bus
#define COM_ACK_CHAR "A"///< Character representing an ACK on the serial bus
#define CHAR_LINE_FEED '\n' ///< Represents an LF character literal
#define CHAR_SPACE ' ' ///< Represents a space character literal
#define BLANK_STRING "" ///< Represents a blank string literal

enum COMMAND_TYPE {COMMAND_GET, COMMAND_SET, COMMAND_ACK};
enum DATA_TYPE { TYPE_DIGITAL, TYPE_ANALOG, TYPE_SERVO };

class RControl
{
    private:
    RNetServer m_server;

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

    public:

    
    RControl(RNetServer &server);


    void getJoystick(int &xaxis, int &yaxis);


    void getButton(int button, bool &state);
};