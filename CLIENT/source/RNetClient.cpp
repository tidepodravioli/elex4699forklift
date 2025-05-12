#include "../headers/RNetClient.hpp"

bool RNetClient::connect(string IPaddr, int port)
{
    consoleout("Attempting connection...");
    connect_socket(IPaddr, port);

    this_thread::sleep_for(chrono::milliseconds(1000));

    consoleout("Testing connection...");
    if(checkAlive())
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

void RNetClient::sendEvent(RControlEvent event)
{
    tx_str(event.asCommand());
}

void RNetClient::consoleout(const string message)
{
    cout << "RNetClient : " << message << endl;
}

bool RNetClient::checkAlive()
{
  tx_str(CLIENT_TX_REQ);
  this_thread::sleep_for(chrono::milliseconds(10));
  
  string ack;
  rx_str(ack);
  
  return ack.compare(CLIENT_RX_ACK) >= 0;
}

bool RNetClient::connected()
{
  return m_flagConnected;
}