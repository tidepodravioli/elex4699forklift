#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <pigpio.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <chrono>
#include <functional>
#include <map>
#include <utility>

#include "../shared/headers/RControlEvent.hpp"
#include "../shared/headers/RJoystickEvent.hpp"


#include "RPiForklift.hpp"
#include "RMotorDriverF.hpp"
#include "RPiServo.hpp"
#include "RNetServer.hpp"
#include "RVidStream.hpp"


#include "ForkliftConstants.h"
#include "build_info.hpp"


/**
 * @brief Main object class for the Forklift project
 * 
 */
class RForkliftManager
{
    private:
    RMotorDriverF * m_driver;
    RPiForklift * m_forklift;

    cv::VideoCapture m_camera;
    RVidStream * m_stream;

    RNetServer m_server;
    
    // For command handling
    using CommandKey = std::pair<EVENT_COMMAND_TYPE, EVENT_DATA_TYPE>;
    using CommandHandler = std::function<bool(RForkliftManager *, RControlEvent &)>;
    
    std::vector<RControlEvent> m_commandQueue;
    std::map<CommandKey, CommandHandler> m_commandHandlers;

    bool m_flagRun = false;
    bool m_flagAutoAvailable = true;

    std::string m_frontCamIP;
    int m_frontCamPort;

    void setNonBlocking(bool enable);
    void setRawMode(bool enable);

    void registerCommands();
    void handleCommand(RControlEvent &cmd);

    bool com_setAnalog(int origin, std::vector<int> values);
    bool com_setCommand(int origin, std::vector<std::string> values);
    bool com_getCommand(int origin, std::vector<std::string> values);
    bool com_setDigital(int origin, std::vector<bool> values);

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
};