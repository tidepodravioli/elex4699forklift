#pragma once

#include "../../CLIENT/headers/ext/CControl.h"
#include <vector>

using namespace std;

class RControlEvent
{
    protected:
    DATA_TYPE m_type;
    vector<int> m_data;
    int m_origin;

    public:
    RControlEvent(DATA_TYPE type, int origin, int value);
    RControlEvent(DATA_TYPE type, int origin, vector<int> values);

    DATA_TYPE getType();
    int getOrigin();
    int getValue();
    vector<int> getValues();
};