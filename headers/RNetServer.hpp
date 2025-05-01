#pragma once

#include <string>
#include <thread>
#include <vector>

#include "ext/server.h"

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

    void startServer(int port);

    void stopServer();

    bool getCom(vector<string> &commands);

    void sendCom(string command);
};