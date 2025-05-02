#pragma once

#include <vector>
#include <pigpio.h>

#include "RPiCamera.hpp"
#include "RPiForklift.hpp"
#include "RMotorDriver.hpp"
#include "RPiServo.hpp"
#include "RNetServer.hpp"
#include "../shared/headers/RControlEvent.hpp"
#include "../shared/headers/RJoystickEvent.hpp"

#define MOTOR_L1 4
#define MOTOR_L2 17
#define MOTOR_R1 27
#define MOTOR_R2 22

#define FORKLIFT_SERVO 18

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
    RNetServer m_server;

    vector<RControlEvent> m_commandQueue;

    bool m_flagRun = false;

    public:
    RForkliftManager();

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