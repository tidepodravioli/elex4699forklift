#include "RControlEvent.hpp"
#include "ext/CJoystickPosition.hpp"

class RJoystickEvent : public RControlEvent
{
    private:

    public:
    RJoystickEvent(CJoystickPosition &val) : RControlEvent(TYPE_ANALOG, {val.percentX(), val.percentY()}) {}
    
};