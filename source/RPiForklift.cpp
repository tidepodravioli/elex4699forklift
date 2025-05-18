#include "../headers/RPiForklift.hpp"

RPiForklift::RPiForklift(int gpioPin) : RPiServo(gpioPin)
{
    m_servoPositions[FLOOR] = FLOOR_POSITION;
    m_servoPositions[UP] = UP_POSITION;
    m_servoPositions[FLOOR2] = FLOOR2_POSITION;
    m_servoPositions[UP2] = UP2_POSITION;
}


void RPiForklift::writePosition(LIFT_POSITION position)
{
    auto pos = m_servoPositions.find(position);
    if(pos != m_servoPositions.end())
    {
        write(pos->second);
    }
    
    //if no match in dictionary, do nothing
}

void RPiForklift::forkUp()
{

}

void RPiForklift::forkDown()
{

}