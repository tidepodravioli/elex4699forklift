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

int RJoystickEvent::percentX()
{
    return m_joystick.percentX();
}

int RJoystickEvent::percentY()
{
    return m_joystick.percentY();
}

CJoystickPosition RJoystickEvent::getObj()
{
    return m_joystick;
}

string RJoystickEvent::getPositionName(bool simple)
{
    JOYSTICK_DIRECTION dir;
    if(simple) dir = m_joystick.get_simple_direction();
    else dir = m_joystick.get_direction();

    switch(dir)
    {
        case JOYSTICK_DIRECTION_NORTH:
                return "NORTH";
                break;
            case JOYSTICK_DIRECTION_NORTHEAST:
                return "SOUTHWEST";
                break;
            case JOYSTICK_DIRECTION_EAST:
                return "WEST";
                break;
            case JOYSTICK_DIRECTION_SOUTHEAST:
                return "NORTHWEST";
                break;
            case JOYSTICK_DIRECTION_SOUTH:
                return "NORTH";
                break;
            case JOYSTICK_DIRECTION_SOUTHWEST:
                return "NORTHEAST";
                break;
            case JOYSTICK_DIRECTION_WEST:
                return "EAST";
                break;
            case JOYSTICK_DIRECTION_NORTHWEST:
                return "SOUTHEAST";
                break;
            case JOYSTICK_DIRECTION_CENTER:
                return "CENTER";
                break;
            default:
                return "DEAD ZONE";
                break;
    }
}