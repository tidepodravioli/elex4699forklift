#pragma once

#include <chrono>
#include "RPiHMotor.hpp"

#define LEFT_MOTOR_SPEED_OFFSET 0
#define RIGHT_MOTOR_SPEED_OFFSET 0

#define TOP_SPEED_PWM 255

class RMotorDriver
{
    private:
    RPiHMotor * m_leftMotor;
    RPiHMotor * m_rightMotor;

    public:
    RMotorDriver(int left1, int left2, int right1, int right2);

    void forward();

    void backward();
    
    void turnLeft(int speed = TOP_SPEED_PWM);

    void turnRight(int speed = TOP_SPEED_PWM);

    void drive(int speed);

    void write(int leftSpeed, int rightSpeed, bool useOffset = false);
};