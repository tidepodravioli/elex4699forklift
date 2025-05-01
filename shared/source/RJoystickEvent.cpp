#include "../headers/RJoystickEvent.hpp"

bool RJoystickEvent::atRest()
{
    return m_joystick.get_simple_direction() == JOYSTICK_DIRECTION_CENTER;
}

bool RJoystickEvent::active()
{
    return !atRest();
}

int RJoystickEvent::getX()
{
    return m_joystick.getX();
}

int RJoystickEvent::getY()
{
    return m_joystick.getY();
}