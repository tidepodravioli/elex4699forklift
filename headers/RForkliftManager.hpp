#pragma once

#include <vector>

#include "RPiCamera.hpp"
#include "RPiForklift.hpp"
#include "RMotorDriver.hpp"
#include "RPiServo.hpp"
#include "../shared/headers/RControlEvent.hpp"

#define MOTOR_L1 0
#define MOTOR_L2 0
#define MOTOR_R1 0
#define MOTOR_R2 0

#define FORKLIFT_SERVO 0

using namespace std;

/**
 * @brief Main object class for the Forklift project
 * 
 */
class RForkliftManager
{
    private:
    RMotorDriver * m_driver;
    RPiForklift * m_forklift;

    vector<RControlEvent> m_commandQueue;

    bool m_flagRun = false;

    public:
    RForkliftManager() {}

    /**
     * @brief Configures physical and network interfaces to prepare for execution
     * 
     */
    void start();

    /**
     * @brief Loads the command queue in from the buffer
     * 
     */
    void getCom();

    /**
     * @brief Interprets the first command in the queue
     * 
     */
    void update();

    /**
     * @brief Based on the command, do something
     * 
     */
    void react();
};