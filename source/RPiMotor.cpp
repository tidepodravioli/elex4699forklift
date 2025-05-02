#include "../headers/RPiMotor.hpp"

RPiMotor::RPiMotor(int gpioPin)
{
    gpioInitialise();

    gpioSetMode(gpioPin, PI_OUTPUT);
    m_gpioPin = gpioPin;
}

void RPiMotor::motorWrite(int speed)
{
    gpioPWM(m_gpioPin, speed);
}

void RPiMotor::motorRun()
{
    gpioWrite(m_gpioPin, 1);
}

void RPiMotor::motorStop()
{
    gpioWrite(m_gpioPin, 0);
}