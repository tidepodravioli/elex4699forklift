
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#include "ext/Client.h"

#define TX_REQ "REQ E4699FMK1\n"
#define RX_ACK "ACK MK1FE4699\n"

using namespace std;

class RNetClient
{
    private:
    bool m_flagConnected = false;
    CClient m_client;
    void consoleout(const string message);

    public:
    RNetClient(){}

    bool connect(string IPaddr, int port);

    void disconnect();
};