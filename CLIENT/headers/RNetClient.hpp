#pragma once

#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#include "../../shared/headers/ext/Client.h"
#include "../../shared/headers/RControlEvent.hpp"
#include "../../shared/headers/RJoystickEvent.hpp"

#define CLIENT_TX_REQ "G 2 0 E4699FMK2"
#define CLIENT_RX_ACK "A 2 0 E4699FMK2"

using namespace std;

class RNetClient : private CClient
{
private:
    bool m_flagConnected = false;
    void consoleout(const string message);
    
public:
    RNetClient() {}

    bool connect(string IPaddr, int port);

    void disconnect();

    void sendEvent(RControlEvent event);

    bool checkAlive();

    bool connected();
};