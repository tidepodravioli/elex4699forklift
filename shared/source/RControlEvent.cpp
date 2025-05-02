#include "../headers/RControlEvent.hpp"

RControlEvent::RControlEvent(DATA_TYPE type, int origin, int value)
{
    m_type = type;
    m_origin = origin;
    m_data.push_back(value);
}

RControlEvent::RControlEvent(DATA_TYPE type, int origin, vector<int> values)
{
    m_type = type;
    m_origin = origin;
    m_data = values;
}

RControlEvent::RControlEvent(string packet)
{
    vector<string> parts = delimitString(packet, ' ');

    m_type = str_to_type(parts[1]);
    m_origin = stoi(parts[2]);
    
    if(parts.size() > 4)
    {
        for(int i = 3; i < parts.size(); i++)
        {
            m_data.push_back(stoi(parts[i]));
        }
    }
    else
    {
        m_data = {stoi(parts[3])};
    }
}

DATA_TYPE RControlEvent::getType()
{
    return m_type;
}

int RControlEvent::getOrigin()
{
    return m_origin;
}

int RControlEvent::getValue()
{
    return m_data[0];
}

vector<int> RControlEvent::getValues()
{
    return m_data;
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


DATA_TYPE RControlEvent::str_to_type(string type)
{
    int typeint = stoi(type);

    switch(typeint)
    {
        case 0:
        return TYPE_DIGITAL;
        break;

        case 1:
        return TYPE_ANALOG;
        break;

        case 2:
        return TYPE_SERVO;
        break;

        default:
        return TYPE_INVALID;
        break;
    }
}