#include "../headers/RControl.hpp"

RControl::RControl(RNetServer &server)
{

}

void RControl::getJoystick(int &xaxis, int &yaxis)
{
    const string COMMAND_X = commandBuilder(COMMAND_GET, TYPE_ANALOG, 0);
    const string COMMAND_Y = commandBuilder(COMMAND_GET, TYPE_ANALOG, 1);

    string ackX, ackY;
    
    m_server.sendCom(COMMAND_X);
    m_server.awaitCom(ackX);

    m_server.sendCom(COMMAND_Y);
    m_server.awaitCom(ackY);

    
}

void RControl::getButton(int button, bool &state)
{

}

string RControl::commandBuilder(COMMAND_TYPE command, DATA_TYPE datatype, int channel, bool addEndl = true, int val)
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