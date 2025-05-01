#include "../headers/RNetClient.hpp"

bool RNetClient::connect(string IPaddr, int port)
{
    consoleout("Attempting connection...");
    m_client.connect_socket(IPaddr, port);

    thread::this_

    consoleout("Testing connection...");
    m_client.tx_str(TX_REQ);

    string response;
    m_client.rx_str(response);

    if(response.compare(RX_ACK) >= 0)
    {
        consoleout("Connected successfully.");
        m_flagConnected = true;
        return true;
    }
    else
    {
        consoleout("Unexpected or no response.");
        m_flagConnected = false;
        return false;
    }
}

void RNetClient::disconnect()
{
    m_client.close_socket();
}


void RNetClient::consoleout(const string message)
{
    cout << "RNetClient : " << message << endl;
}