#include "RPiMotor.hpp"

/**
 * @brief Represents an interface to an H-bridge connected to a motor
 * Forwards here means a signal on pin1, while pin2 is held LOW
 * Backwards is the reverse of this.
 * 
 */
class RPiHMotor
{
    private:
    int m_pin1, m_pin2;

    public:
    /**
     * @brief Initializes an H-bridge interface on the given pins
     * 
     * @param pin1 GPIO pin enable 1
     * @param pin2 GPIO pin enable 2
     */
    RPiHMotor(int pin1, int pin2);

    /**
     * @brief Runs the motor at the given speed
     * 
     * @param speed The PWM value to write to the H-bridge (negative is reverse)
     */
    void motorWrite(int speed);

    /**
     * @brief Runs the motor at full speed in the given direction
     * 
     * @param forward Whether the motor should run forward or backwards
     */
    void motorRun(bool forward = true);

    /**
     * @brief Stops the motor
     * 
     */
    void motorStop();
};