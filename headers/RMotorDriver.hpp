#pragma once

#include <chrono>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "RPiHMotor.hpp"


#include "ForkliftConstants.h"

using namespace std;

/**
 * @brief Represents an interface to two motors connected to an H-bridge
 * @details RMotorDriver uses two RPiHMotor interfaces to drive the robot around.
 * It provides simple forward, backward, and spin movement, but also more complex
 * operations that involve driving at different speeds, as well as manual driving 
 * with a joystick
 */
class RMotorDriver
{
    protected:
    RPiHMotor * m_leftMotor;
    RPiHMotor * m_rightMotor;
    
    float processAxis(int raw);
    void arcadeDrive(int pX, int pY, int &leftMotor, int &rightMotor);

    bool m_flagSlowMode = false;
    int m_topSpeedPWM = TOP_SPEED_PWM;

    public:
    RMotorDriver(int left1, int left2, int right1, int right2);

    /**
     * @brief Drives both motors forawrd at full speed
     * 
     */
    void forward();

    /**
     * @brief Drives both motors backward at full speed
     * 
     */
    void backward();

    /**
     * @brief Drives both motors at full speed in opposite directions, such that it spins left
     * 
     */
    void left();

    /**
     * @brief Drives both motors at full speed in opposite directions, such that it spins right
     * 
     */
    void right();

    /**
     * @brief Stops both motors
     * 
     */
    void stop();

    /**
     * @brief Sets the motors to run at a slower default speed
     * 
     */
    void slowMode();

    /**
     * @brief Sets the motors to run at the highest possible speed
     * 
     */
    void normalMode();

    /**
     * @brief Toggles the slow mode
     * 
     * @return true if slow mode was enabled
     * @return false if slow mode was disabled
     */
    bool toggleSlow();
    
    /**
     * @brief Spins left at a given speed
     * 
     * @param speed The speed to spin left at (0-255)
     */
    void turnLeft(int speed = TOP_SPEED_PWM);

    /**
     * @brief Spins right at a given speed
     * 
     * @param speed The speed to spin right at (0-255)
     */
    void turnRight(int speed = TOP_SPEED_PWM);

    /**
     * @brief Drives both motors at a given speed
     * 
     * @param speed The speed to run the motors at
     * @param useOffset Whether or not to use an offset for the speed
     */
    void drive(int speed, bool useOffset = false);

    /**
     * @brief Writes a speed to each motor individually, with an optional offset
     * 
     * @param leftSpeed Speed to run the left motor at
     * @param rightSpeed Speed to run the right motor at
     */
    void write(int leftSpeed, int rightSpeed);

    /**
     * @brief Drives the motors such that it matches the input of a joystick
     * 
     * @param pX x-axis value (0-100)
     * @param pY y-axis value (0-100)
     */
    void joystickDrive(int pX, int pY);
};