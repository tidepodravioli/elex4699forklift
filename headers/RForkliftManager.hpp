#pragma once

#include "RPiCamera.hpp"
#include "RPiForklift.hpp"
#include "RMotorDriver.hpp"
#include "RPiServo.hpp"

#define MOTOR_L1 0
#define MOTOR_L2 0
#define MOTOR_R1 0
#define MOTOR_R2 0

#define FORKLIFT_SERVO 0

/**
 * @brief Main object class for the Forklift project
 * 
 */
class RForkliftManager
{
    private:
    RMotorDriver * m_driver;
    RPiForklift * m_forklift;

    bool m_flagRun = false;

    public:
    RForkliftManager() {}

    /**
     * @brief Configures physical and network interfaces to prepare for execution
     * 
     */
    void start();

    /**
     * @brief Get the Com object
     * 
     */
    void getCom();

    void update();

    void react();
};