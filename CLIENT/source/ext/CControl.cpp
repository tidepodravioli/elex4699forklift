#include "../../headers/ext/CControl.h"

using namespace std;

CControl::CControl()
{
  auto time_now = std::chrono::steady_clock::now();
  for(int button = 0; button < BUTTON_NUM_OF_CHANNELS; button++)
  {
    m_lastDebounceTimes[button] = time_now;
  }
}

CControl::~CControl()
{
    
}

void CControl::init_com(int comport)
{
  stringstream portName;
  portName << "COM" << comport;
  
  cout << "Opening " << portName.str() << endl;
  
  m_com.~Serial();
  m_com = Serial();
  m_com.open(portName.str());

  if(m_com.is_open())
  {
    m_flagPortOpen = true;
    cout << "Port is open." << endl;
  }
  else
  {
    m_flagPortOpen = false;
    cout << "Port is closed." << endl;
  } 
}

bool CControl::get_data (DATA_TYPE type, int channel, int &result)
{
  if(m_com.is_open())
  {
    // Builds the command that is to be sent to the microcontroller
    string command = commandBuilder(COMMAND_GET, type, channel);
    int size = command.length();

    // Changes the string to a char * buffer and sends out the command
    const char * buffer = command.c_str();
    m_com.write(buffer, size);

    // Read the response from the microcontroller
    string message;
    if(!readMessage(message)) //If the message was not able to be read, return false
      return false;
    
    string correctResponse = commandBuilder(COMMAND_ACK, type, channel, false);
    if(message.compare(correctResponse) > 0)
    {
      vector<string> parts = delimitString(message, CHAR_SPACE);

      if(parts.size() == 4)
      {
        result = stoi(parts[3]);
        return true;
      }
      else return false;
    }
    else return false;
  }
  else
  {
    return false;
  }
}

bool CControl::set_data(DATA_TYPE type, int channel, int val)
{
  if(m_com.is_open())
  {
    // Builds the command that is to be sent to the microcontroller
    string command = commandBuilder(COMMAND_SET, type, channel, true, val);
    int size = command.length();

    // Changes the string to a char * buffer and sends out the command
    const char * buffer = command.c_str();
    m_com.write(buffer, size);

    // Read the response from the microcontroller
    string message;
    if(!readMessage(message)) //If the message was not able to be read, return false
      return false;
    
    // Checks to see if the acknowledgement message matches what it should be
    string correctResponse = commandBuilder(COMMAND_ACK, type, channel, false, val);
    if(correctResponse.compare(message) == 0) return true;
    else return false;
  }
  else
  {
    return false;
  }
}

vector<string> CControl::delimitString(std::string input, char delimiter)
{
    vector<string> parts;
    string builder = BLANK_STRING;
    for(int charPosition = 0; charPosition < input.size(); charPosition++)
    {
      if(charPosition == input.size() - 1)
        builder += input.at(charPosition); 

      if(input.at(charPosition) == delimiter || charPosition == input.size() - 1) 
      {
        parts.push_back(builder);
        builder = BLANK_STRING;
      }
      else builder += input.at(charPosition);
    }

    return parts;
}

string CControl::commandBuilder(COMMAND_TYPE command, DATA_TYPE datatype, int channel, bool addEndl, int val)
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

bool CControl::readMessage(string &result)
{
  if(m_com.is_open())
  {
    // Creates a buffer for the acknowledgement message
    char * acknowledgement = new char[CHAR_ARRAY_MAX_SIZE];
    int sizeAck = -1;

    // Reads the message from the serial monitor when it's available
    auto startTime = std::chrono::steady_clock::now();
    while(true)
    {
      sizeAck = m_com.read(acknowledgement, CHAR_ARRAY_MAX_SIZE);

      if(sizeAck > 0) break;

      // * ChatGPT code that has been modified
      // waits SERIAL_PORT_DELAY ms every time the loop is run, up to SERIAL_PORT_TIMEOUT ms.
      auto elapsed_time = std::chrono::steady_clock::now() - startTime;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() > SERIAL_PORT_TIMEOUT) {
            return false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SERIAL_PORT_DELAY));
    }
    m_com.flush();

    string message = acknowledgement;
    message = message.substr(0, sizeAck - 1);

    result = message;
    return true;
  }
  else return false;
}

CJoystickPosition CControl::get_analog(bool &pass)
{
  if(m_com.is_open())
  {
    int _result1, _result2;
    bool success = get_data(TYPE_ANALOG, CH_JOYSTICK_X, _result1);
    success &= get_data(TYPE_ANALOG, CH_JOYSTICK_Y, _result2);

    if(success)
    {
      if(_result1 >= 0 && _result2 >= 0) pass = true;
      else pass = false;

      return CJoystickPosition(_result1, _result2);
    }
    else 
    {
      pass = false;
      return CJoystickPosition();
    }
  }
  else
  {
    pass = false;
    return CJoystickPosition();
  }
}

bool CControl::get_button(int channel)
{
  int result = -1;
  get_data(TYPE_DIGITAL, channel, result);

  if(result == 1)
  {
    m_lastDebounceTimes[channel] = chrono::steady_clock::now();
    m_buttonActive[channel] = false;
    return false;
  }
  else if(result == 0)
  {
    auto elapsed_time = chrono::steady_clock::now() - m_lastDebounceTimes[channel];
    //cout << chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() << endl;
    if(!m_buttonActive[channel] && chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() > BUTTON_DEBOUNCE_TIMEOUT)
    {
      m_buttonActive[channel] = true;
      return true;
    }

    return false;
  }

}

bool CControl::checkPort()
{
  if(m_flagPortOpen)
  {
    string command = COM_CHECK_ALIVE;
    command += CHAR_LINE_FEED;
    const char * buffer = command.c_str();
    int len = command.length();

    m_com.flush();
    m_com.write(buffer, len);

    string message = "";
    if(readMessage(message))
    {
      if(message.compare(COM_ACK_ALIVE) == 0)
        return true;
      else return false;
    } 
    else return false;
  }
  else return false;
}

bool CControl::findPort()
{
  for(int portNum = 0; portNum <= SERIAL_PORT_CHECK_TO_MAX; portNum++)
  {
    init_com(portNum);
    if(checkPort()) return true;
  }

  return false;
}