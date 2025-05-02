#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <conio.h>

#include "ext/getstuff.h"
#include "ext/CControl.h"

#include "RNetClient.hpp"

#define E4618_IPADDR_REGEX "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$"


using namespace std;
using namespace raf_cin;

class RForkliftClient
{
    private:
    CControl m_serial;
    RNetClient m_network;

    bool m_flagConnected = false;

    void gui_getSocket();
    void gui_startClient();

    void gui_IOTest();

    public:
    RForkliftClient() {}

    void start();

    
};