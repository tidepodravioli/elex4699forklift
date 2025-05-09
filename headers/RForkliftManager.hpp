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
#include "RArUcoReader.hpp"

#include "ForkliftConstants.h"

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