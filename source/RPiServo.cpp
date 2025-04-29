#include "../headers/RPiServo.hpp"

RPiServo::RPiServo(int gpioPin)
{
    m_servopin = gpioPin;
    gpioSetMode(gpioPin, PI_OUTPUT);
}

void RPiServo::write(int degrees)
{
    const int write_us = (2000/180) * (degrees) + 500; //degrees to microseconds
    writeus(write_us);
}

void RPiServo::writeus(int microseconds)
{
    gpioServo(m_servopin, microseconds);
}

int RPiServo::getLastWrite()
{
    return m_lastDegree;
}

int RPiServo::getLastWriteus()
{
    return m_lastus;
}