#pragma once

#include <string>
#include <thread>
#include <vector>

#include "../shared/headers/ext/server.h"
#include "../shared/headers/RControlEvent.hpp"

#include "ForkliftConstants.h"

using namespace std;

/**
 * @brief Provides the main TCP/IP communication between the forklift and the computer
 * @details RNetServer uses Craig's CClient/CServer architecture to communicate commands
 * between the forklift and the client computer.
 */
class RNetServer : public CServer
{
    private:
    bool m_flagCloseServer = false;
    void server_start(int port); 

    public:
    RNetServer();

    void startServer(int port = SERVER_PORT);

    void stopServer();

    bool getCom(vector<string> &commands);

    bool getCom(vector<RControlEvent> &events);

    void sendCom(string command);
};