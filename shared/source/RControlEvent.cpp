#include "../headers/RControlEvent.hpp"

RControlEvent::RControlEvent()
{
    m_com = ECOMMAND_INVALID;
    m_type = ETYPE_INVALID;
    m_origin = -1;
    m_data = {};
}

RControlEvent::RControlEvent(EVENT_COMMAND_TYPE com, EVENT_DATA_TYPE type, int origin, int value)
{
    m_com = com;
    m_type = type;
    m_origin = origin;
    
    m_data.push_back(to_string(value));
}

RControlEvent::RControlEvent(EVENT_COMMAND_TYPE com, EVENT_DATA_TYPE type, int origin, vector<int> values)
{
    m_com = com;
    m_type = type;
    m_origin = origin;
    
    for(int i : values)
    {
        m_data.push_back(to_string(i));
    }
}

RControlEvent::RControlEvent(EVENT_COMMAND_TYPE com, EVENT_DATA_TYPE type, int origin, vector<string> values)
{
    m_com = com;
    m_type = type;
    m_origin = origin;
    
    m_data.insert(m_data.begin(), values.begin(), values.end());
}

EVENT_COMMAND_TYPE RControlEvent::getCom()
{
    return m_com;
}

EVENT_DATA_TYPE RControlEvent::getType()
{
    return m_type;
}

void RControlEvent::setCom(EVENT_COMMAND_TYPE type)
{
    m_com = type;
}

int RControlEvent::getOrigin()
{
    return m_origin;
}

int RControlEvent::getValue()
{
    int result = -1;
    try
    {
        result = stoi(m_data[0]);
        return result;
    }
    catch(const std::exception& e)
    {
        return result;
    }
        
}

vector<string> RControlEvent::getValues()
{
    return m_data;
}

string RControlEvent::asCommand(bool newline)
{
    return commandBuilder(m_com, m_type, m_origin, m_data, newline);
}

RControlEvent RControlEvent::copy()
{
    return RControlEvent(m_com, m_type, m_origin, m_data);
}

string RControlEvent::commandBuilder(EVENT_COMMAND_TYPE command, EVENT_DATA_TYPE datatype, int channel, vector<string> vals, bool addEndl)
{
    stringstream _commandBuilder;
  switch(command)
  {
    case ECOMMAND_GET:
      _commandBuilder << COM_GET_CHAR;
      break;
    case ECOMMAND_SET:
      _commandBuilder << COM_SET_CHAR;
      break;
    case ECOMMAND_ACK:
      _commandBuilder << COM_ACK_CHAR;
      break;
  }
  _commandBuilder << CHAR_SPACE;

  _commandBuilder  << (int)datatype << CHAR_SPACE;

  _commandBuilder << channel;

  if(!vals.empty())
  {
    for(string val : vals)
    {
      _commandBuilder << CHAR_SPACE << val;
    }
  }
  
  if(addEndl)
    _commandBuilder << endl;

  return _commandBuilder.str();
}

RControlEvent RControlEvent::parse(string command)
{
    try
    {
        vector<string> parts = delimitString(command, ' ');

        //PARSE COMMAND TYPE
        const char c_com =  parts[0][0];
        EVENT_COMMAND_TYPE com = str_to_com(c_com);

        //PARSE DATA TYPE
        EVENT_DATA_TYPE typ = str_to_type(parts[1]);

        //PARSE ORIGIN
        int origin = stoi(parts[2]);

        //PARSE DATA
        vector<string> data;

        if(parts.size() > 3)
        {
            data.insert(data.begin(), parts.begin() + 3, parts.end());
        }

        return RControlEvent(com, typ, origin, data);
    }
    catch(const std::exception& e)
    {
        return RControlEvent();
    }
    
}

vector<string> RControlEvent::delimitString(std::string input, char delimiter)
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

EVENT_COMMAND_TYPE RControlEvent::str_to_com(char com)
{
    switch(com)
    {
        case 'G':
        return ECOMMAND_GET;
        break;

        case 'S':
        return ECOMMAND_SET;
        break;

        case 'A':
        return ECOMMAND_ACK;
        break;

        default:
        return ECOMMAND_INVALID;
        break;
    }
}

EVENT_DATA_TYPE RControlEvent::str_to_type(string type)
{
    int typeint = stoi(type);

    switch(typeint)
    {
        case 0:
        return ETYPE_DIGITAL;
        break;

        case 1:
        return ETYPE_ANALOG;
        break;

        case 2:
        return ETYPE_COMMAND;
        break;

        default:
        return ETYPE_INVALID;
        break;
    }
}