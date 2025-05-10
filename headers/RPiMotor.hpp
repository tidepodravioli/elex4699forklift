#pragma once

#include <pigpio.h>

/**
 * @brief Represents a motor connected to the RPI GPIO pins
 * @details RPiMotor uses the PIGPIO library to directly drive a
 * motor that is connected directly to the GPIO pins. It writes
 * PWM values to the pin to vary the speed.
 */
class RPiMotor
{
    private:
    int m_gpioPin;
    
    public:
    /**
     * @brief Inititializes a PIGPIO motor on the given IO pin.
     * 
     * @param gpioPin GPIO pin the motor is on
     */
    RPiMotor(int gpioPin);

    /**
     * @brief Writes the given value to the motor.
     * 
     * @param speed PWM value to write to the motor
     */
    void motorWrite(int speed);

    /**
     * @brief Starts the motor at full speed (HIGH)
     * 
     */
    void motorRun();

    /**
     * @brief Stops the motor (LOW)
     * 
     */
    void motorStop();
};