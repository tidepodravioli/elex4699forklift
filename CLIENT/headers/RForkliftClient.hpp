#pragma once

#include <iostream>
#include <chrono>
#include <regex>
#include <string>
#include <conio.h>

#include "ext/getstuff.h"
#include "ext/CControl.h"

#include "RNetClient.hpp"
#include "RVidReceiver.hpp"
#include "RDraw.hpp"

#define E4618_IPADDR_REGEX "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$"



class RForkliftClient
{
private:
    CControl m_serial;
    RNetClient m_network;
    RDraw m_ui;

    std::chrono::steady_clock::time_point m_lastEvent;

    bool m_flagConnected = false;

    void cli_getSocket();
    void cli_startClient();

    void cli_IOTest();
    void gui_UITest();
    void cli_streamTest();
    

    void cli_showMenu();

public:
    RForkliftClient() {}

    void start();
};