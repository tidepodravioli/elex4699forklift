#include <vector>

#include "RControlEvent.hpp"
#include "ext/CJoystickPosition.hpp"

using namespace std;

class RJoystickEvent : public RControlEvent
{
    private:
    CJoystickPosition m_joystick;

    public:
    RJoystickEvent(CJoystickPosition &val) : RControlEvent(TYPE_ANALOG, 0, { val.getX(), val.getY()}) { m_joystick = val; }
    RJoystickEvent(RControlEvent event) : RControlEvent(TYPE_ANALOG, 0, event.getValues())
    { 
        m_joystick = CJoystickPosition(m_data[0], m_data[1]);
    }

    bool atRest();

    bool active();

    int getX();

    int getY();
};