#include "../headers/RMotorDriver.hpp"

RMotorDriver::RMotorDriver(int left1, int left2, int right1, int right2)
{
    m_leftMotor = new RPiHMotor(left1, left2);
    m_rightMotor = new RPiHMotor(right2, right2);
}

void RMotorDriver::write(int leftSpeed, int rightSpeed, bool useOffset)
{
    if(useOffset)
    {
        m_leftMotor->motorWrite(leftSpeed + LEFT_MOTOR_SPEED_OFFSET);
        m_rightMotor->motorWrite(rightSpeed + RIGHT_MOTOR_SPEED_OFFSET);
    }
    else
    {
        m_leftMotor->motorWrite(leftSpeed);
        m_rightMotor->motorWrite(rightSpeed);
    }
}

void RMotorDriver::drive(int speed)
{
    write(speed, speed);
}

void RMotorDriver::forward()
{
   drive(TOP_SPEED_PWM);
}

void RMotorDriver::backward()
{
    drive(-1 * TOP_SPEED_PWM);
}

void RMotorDriver::turnLeft(int speed)
{
    if(speed > 0)
    {
        write(-1 * speed, speed);
    }
}

void RMotorDriver::turnRight(int speed)
{
    if(speed > 0)
    {
        write(speed, -1 * speed);
    }
}