#pragma once

#include <iostream>
#include <chrono>
#include <regex>
#include <string>
#include <conio.h>

#include "ext/getstuff.h"
#include "ext/CControl.h"

#include "RNetClient.hpp"
#include "RDraw.hpp"

#define E4618_IPADDR_REGEX "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$"


using namespace std;
using namespace raf_cin;

class RForkliftClient
{
    private:
    CControl m_serial;
    RNetClient m_network;
    RDraw m_ui;

    chrono::steady_clock::time_point m_lastEvent;

    bool m_flagConnected = false;

    void gui_getSocket();
    void gui_startClient();

    void gui_IOTest();
    void gui_UITest();

    void gui_showMenu();

    public:
    RForkliftClient() {}

    void start();

    
};