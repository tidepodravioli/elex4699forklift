#pragma once

#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#include "ext/Client.h"
#include "../../shared/headers/RControlEvent.hpp"
#include "../../shared/headers/RJoystickEvent.hpp"

#define CLIENT_TX_REQ "REQ E4699FMK1\n"
#define CLIENT_RX_ACK "ACK MK1FE4699\n"

using namespace std;

class RNetClient
{
    private:
    bool m_flagConnected = false;
    CClient m_client;
    void consoleout(const string message);

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
    string commandBuilder(COMMAND_TYPE command, DATA_TYPE datatype, int channel, int val = -1, bool addEndl = true);
    string commandBuilder(COMMAND_TYPE command, DATA_TYPE datatype, int channel, vector<int> vals = {}, bool addEndl = true);


    public:
    RNetClient(){}

    bool connect(string IPaddr, int port);

    void disconnect();

    void sendEvent(RControlEvent event);
    void sendEvent(RJoystickEvent event);
};