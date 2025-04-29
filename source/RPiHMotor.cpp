#include "../headers/RPiHMotor.hpp"

RPiHMotor::RPiHMotor(int pin1, int pin2)
{
    //Sets both pins as outputs
    gpioSetMode(pin1, PI_OUTPUT);
    gpioSetMode(pin2, PI_OUTPUT);

    //Sets both pins low
    gpioWrite(pin1, 0);
    gpioWrite(pin2, 0);

    m_pin1 = pin1;
    m_pin2 = pin2;
}

void RPiHMotor::motorWrite(int speed)
{
    if(speed >= 0)
    {
        gpioPWM(m_pin1, speed);
        gpioWrite(m_pin2, 0);
    }
    else
    {
        gpioPWM(m_pin2, speed);
        gpioWrite(m_pin1, 0);
    }
}

void RPiHMotor::motorStop()
{
    gpioWrite(m_pin1, 0);
    gpioWrite(m_pin2, 0);

}