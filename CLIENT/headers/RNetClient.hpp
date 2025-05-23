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


class RNetClient : private CClient
{
private:
    bool m_flagConnected = false;
    void consoleout(const std::string message);
    
public:
    RNetClient() {}

    using CClient::tx_str;

    bool connect(std::string IPaddr, int port);

    void disconnect();

    void sendEvent(RControlEvent event);

    RControlEvent waitAck(int timeout_ms = -1);

    bool checkAlive();

    bool connected();
};