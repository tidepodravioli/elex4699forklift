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