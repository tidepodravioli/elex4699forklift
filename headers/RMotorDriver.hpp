#pragma once

#include <chrono>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "RPiHMotor.hpp"


#include "ForkliftConstants.h"

using namespace std;

class RMotorDriver
{
    private:
    RPiHMotor * m_leftMotor;
    RPiHMotor * m_rightMotor;
    
    float processAxis(int raw);
    void arcadeDrive(int pX, int pY, int &leftMotor, int &rightMotor);

    bool m_flagSlowMode = false;
    int m_topSpeedPWM = TOP_SPEED_PWM;

    public:
    RMotorDriver(int left1, int left2, int right1, int right2);

    void forward();

    void backward();

    void left();

    void right();

    void stop();

    void slowMode();

    void normalMode();

    bool toggleSlow();
    
    void turnLeft(int speed = TOP_SPEED_PWM);

    void turnRight(int speed = TOP_SPEED_PWM);

    void drive(int speed);

    void write(int leftSpeed, int rightSpeed, bool useOffset = false);

    void joystickDrive(int pX, int pY);
};