#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <pigpio.h>
#include <unistd.h>
#include <sys/types.h>
#include <chrono>

#include "../shared/headers/RControlEvent.hpp"
#include "../shared/headers/RJoystickEvent.hpp"


#include "RPiForklift.hpp"
#include "RMotorDriver.hpp"
#include "RPiServo.hpp"
#include "RNetServer.hpp"

#include "RPiCamera.hpp"
#include "RAutoPilot.hpp"
#include "RAutoFork.hpp"
#include "RArUcoReader.hpp"
#include "RVidStream.hpp"


#include "ForkliftConstants.h"

using namespace std;
using namespace cv;

/**
 * @brief Main object class for the Forklift project
 * 
 */
class RForkliftManager
{
    private:
    RMotorDriver * m_driver;
    RPiForklift * m_forklift;

    VideoCapture m_camera;
    RVidStream * m_stream;

    RAutoPilot * m_autopilot;
    RAutoFork * m_autofork;
    RCoordinateHelper * m_helper;

    RNetServer m_server;

    vector<RControlEvent> m_commandQueue;

    bool m_flagRun = false;
    bool m_flagAutoAvailable = true;

    public:
    RForkliftManager();

    /**
     * @brief Configures physical and network interfaces to prepare for execution
     * 
     */
    void start();

    /**
     * @brief Initializes server services
     * 
     */
    bool init();

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
    void automode();
};