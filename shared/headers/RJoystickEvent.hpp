#include <vector>

#include "RControlEvent.hpp"
#include "ext/CJoystickPosition.hpp"

using namespace std;

class RJoystickEvent : public RControlEvent
{
    private:
    CJoystickPosition m_joystick;

    public:
    RJoystickEvent(CJoystickPosition &val) : RControlEvent(TYPE_ANALOG, 0, { val.percentX(), val.percentY()}) {}

    bool atRest();

    bool active();

    int getX();

    int getY();
};