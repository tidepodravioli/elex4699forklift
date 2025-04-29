#include "RPiMotor.hpp"

/**
 * @brief Represents an interface to an H-bridge connected to a motor
 * 
 */
class RPiHMotor
{
    private:

    public:
    /**
     * @brief Initializes an H-bridge interface on the given pins
     * 
     * @param pin1 GPIO pin enable 1
     * @param pin2 GPIO pin enable 2
     */
    RPiHMotor(int pin1, int pin2);

    
    void motorWrite(int speed);

    void motorStop();
};