#pragma once

#include "ext/CControlTypes.h"
#include <vector>
#include <string>

using namespace std;

class RControlEvent
{
    private:
    vector<string> delimitString(string input, char delimiter);
    DATA_TYPE str_to_type(string type);

    protected:
    DATA_TYPE m_type;
    vector<int> m_data;
    int m_origin;

    public:
    RControlEvent(DATA_TYPE type, int origin, int value);
    RControlEvent(DATA_TYPE type, int origin, vector<int> values);
    RControlEvent(string packet);

    DATA_TYPE getType();
    int getOrigin();
    int getValue();
    vector<int> getValues();
};