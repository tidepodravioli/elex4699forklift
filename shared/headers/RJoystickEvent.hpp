#include <vector>
#include <string>
#include <stdlib.h>

#include "RControlEvent.hpp"
#include "ext/CJoystickPosition.hpp"

using namespace std;

class RJoystickEvent : public RControlEvent
{
    private:
    CJoystickPosition m_joystick;

    public:
    RJoystickEvent(CJoystickPosition &val) : RControlEvent(COMMAND_SET, TYPE_ANALOG, 0, { val.getX(), val.getY()}) { m_joystick = val; }
    RJoystickEvent(RControlEvent event) : RControlEvent(COMMAND_SET, TYPE_ANALOG, 0, event.getValues())
    { 
        int x = stoi(m_data[0]);
        int y = stoi(m_data[1]);
        m_joystick = CJoystickPosition(x, y);
    }

    bool atRest();

    bool active();

    int getX();

    int getY();

    int percentX();

    int percentY();

    CJoystickPosition getObj();

    string getPositionName(bool simple = false);
};