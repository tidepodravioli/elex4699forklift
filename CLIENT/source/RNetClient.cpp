#include "../headers/RNetClient.hpp"

bool RNetClient::connect(string IPaddr, int port)
{
    consoleout("Attempting connection...");
    m_client.connect_socket(IPaddr, port);

    this_thread::sleep_for(chrono::milliseconds(1000));

    consoleout("Testing connection...");
    if(checkAlive())
    {
      consoleout("Connected successfully.");
      m_lastHeartBeat = chrono::system_clock::now();
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
    string command = commandBuilder(COMMAND_ACK, event.getType(), event.getOrigin(), event.getValue());
    m_client.tx_str(command);
}

void RNetClient::sendEvent(RJoystickEvent event)
{
    string command = commandBuilder(COMMAND_ACK, event.getType(), event.getOrigin(), event.getValues());
    m_client.tx_str(command);
    
}

void RNetClient::consoleout(const string message)
{
    cout << "RNetClient : " << message << endl;
}

string RNetClient::commandBuilder(COMMAND_TYPE command, DATA_TYPE datatype, int channel, int val, bool addEndl)
{
    stringstream _commandBuilder;
  switch(command)
  {
    case COMMAND_GET:
      _commandBuilder << COM_GET_CHAR;
      break;
    case COMMAND_SET:
      _commandBuilder << COM_SET_CHAR;
      break;
    case COMMAND_ACK:
      _commandBuilder << COM_ACK_CHAR;
      break;
  }
  _commandBuilder << CHAR_SPACE;

  _commandBuilder  << (int)datatype << CHAR_SPACE;

  _commandBuilder << channel;

  if(val != -1)
    _commandBuilder << CHAR_SPACE << val;

  if(addEndl)
    _commandBuilder << endl;

  return _commandBuilder.str();
}


bool RNetClient::checkAlive()
{
  m_client.tx_str(CLIENT_TX_REQ);
  this_thread::sleep_for(chrono::milliseconds(10));
  
  string ack;
  m_client.rx_str(ack);
  
  return ack.compare(CLIENT_RX_ACK) >= 0;
}

void RNetClient::heartbeat_t()
{
  chrono::system_clock::time_point now = chrono::system_clock::now();
  if((now - m_lastHeartBeat) > chrono::seconds(2 * CLIENT_PERIOD_HEARTBEAT_SEC))
  {
    m_flagConnected = false;
    consoleout("Connection lost");
  }
  
}