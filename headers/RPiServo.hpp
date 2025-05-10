#pragma once

#include <pigpio.h>

/**
 * @brief Provides an interface to control a servo connected to the GPIO pins
 * @details RPiServo uses the PIGPIO library to interface with a servo via PWM.
 * It provides methods to write in either degrees or in microseconds, and a 
 * way to check what the last write was in both units as well.
 */
class RPiServo
{
    protected:

    int m_servopin;
    int m_lastDegree, m_lastus;

    public:

    /**
     * @brief Creates a servo interface on the given pin
     * 
     * @param gpioPin the PIGPIO pin the servo is connected to
     */
    RPiServo(int gpioPin);
    
    /**
     * @brief Changes the position of the servo
     * 
     * @param degrees The angle of the servo arm in degrees
     */
    void write(int degrees);


    /**
     * @brief Changes the position of the servo
     * 
     * @param microseconds The width of the pulse sent to the servo in microseconds
     */
    void writeus(int microseconds);

    /**
     * @brief Gets the last angle written to the servo
     * 
     * @return int The angle in degrees
     */
    int getLastWrite();

    /**
     * @brief Gets the width of the last pulse written to the servo
     * 
     * @return int The pulse width in microseconds 
     */
    int getLastWriteus();
};