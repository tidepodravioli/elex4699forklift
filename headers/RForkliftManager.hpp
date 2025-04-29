#include "RPiCamera.hpp"
#include "RPiForklift.hpp"
#include "RMotorDriver.hpp"
#include "RPiServo.hpp"

#define MOTOR_L1 
#define MOTOR_L2
#define MOTOR_R1
#define MOTOR_R2

/**
 * @brief Main object class for the Forklift project
 * 
 */
class RForkliftManager
{
    private:
    RPiHMotor * m_leftMotor;
    RPiHMotor * m_rightMotor;

    public:
    RForkliftManager() {}

    void start();

};