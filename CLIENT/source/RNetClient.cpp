#include "../headers/RNetClient.hpp"

using namespace std;


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
    close_socket();
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

RControlEvent RNetClient::waitAck(int timeout_ms)
{
  string ack;

  chrono::system_clock::time_point start = chrono::system_clock::now();

  bool timeout = false;
  
  do
  {
    rx_str(ack);
    if(timeout_ms > 0)
      timeout = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count() > timeout_ms - 1000;
  }
  while(ack == "" && !timeout);

  return RControlEvent::parse(ack);
}

bool RNetClient::connected()
{
  return m_flagConnected;
}