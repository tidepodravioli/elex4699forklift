#include "../headers/RMotorDriver.hpp"

RMotorDriver::RMotorDriver(int left1, int left2, int right1, int right2)
{
    m_leftMotor = new RPiHMotor(left1, left2);
    m_rightMotor = new RPiHMotor(right2, right2);
}

void RMotorDriver::forward()
{
    m_leftMotor->motorWrite(255 + LEFT_MOTOR_SPEED_OFFSET);
    m_rightMotor->motorWrite(255 + RIGHT_MOTOR_SPEED_OFFSET);
}

void RMotorDriver::backward()
{
    m_leftMotor->motorWrite(255 + LEFT_MOTOR_SPEED_OFFSET);
    m_rightMotor->motorWrite(255 + RIGHT_MOTOR_SPEED_OFFSET);
}
