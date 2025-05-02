#pragma once

#include <string>
#include <thread>
#include <vector>

#include "ext/server.h"
#include "../shared/headers/RControlEvent.hpp"

#define SERVER_PORT 5008


using namespace std;
class RNetServer
{
    private:
    CServer m_server;
    bool m_flagCloseServer = false;
    void server_start(int port); 

    public:
    RNetServer() {}

    void startServer(int port = SERVER_PORT);

    void stopServer();

    bool getCom(vector<string> &commands);

    bool getCom(vector<RControlEvent> &events);

    void sendCom(string command);
};