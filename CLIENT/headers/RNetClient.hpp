#pragma once

#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#include "../../shared/headers/ext/Client.h"
#include "../../shared/headers/RControlEvent.hpp"
#include "../../shared/headers/RJoystickEvent.hpp"

#define CLIENT_TX_REQ "REQ E4699FMK1\n"
#define CLIENT_RX_ACK "ACK MK1FE4699\n"

#define CLIENT_EXPECTED_HEARTBEAT "HEART MK1FE4699\n"
#define CLIENT_PERIOD_HEARTBEAT_SEC 15

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