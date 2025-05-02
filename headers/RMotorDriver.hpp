#pragma once

#include <chrono>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "RPiHMotor.hpp"


#define LEFT_MOTOR_SPEED_OFFSET 0
#define RIGHT_MOTOR_SPEED_OFFSET 0

#define TOP_SPEED_PWM 255

#define RMOTORDRIVER_JOYSTICK_CENTER 50.0f
#define RMOTORDRIVER_DEADZONE 3.0f       // Deadzone around center
#define RMOTORDRIVER_MAX_INPUT 50.0f     // Joystick value range from center
#define RMOTORDRIVER_MAX_OUTPUT 255.0f   // Max motor speed

using namespace std;

class RMotorDriver
{
    private:
    RPiHMotor * m_leftMotor;
    RPiHMotor * m_rightMotor;
    
    float processAxis(int raw);
    void arcadeDrive(int pX, int pY, int &leftMotor, int &rightMotor);

    public:
    RMotorDriver(int left1, int left2, int right1, int right2);

    void forward();

    void backward();

    void left();

    void right();

    void stop();
    
    void turnLeft(int speed = TOP_SPEED_PWM);

    void turnRight(int speed = TOP_SPEED_PWM);

    void drive(int speed);

    void write(int leftSpeed, int rightSpeed, bool useOffset = false);

    void joystickDrive(int pX, int pY);
};