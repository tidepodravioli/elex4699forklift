#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <pigpio.h>
#include <unistd.h>
#include <sys/types.h>
#include <chrono>
#include <ncurses.h>
#include <functional>
#include <map>
#include <utility>

#include "../shared/headers/RControlEvent.hpp"
#include "../shared/headers/RJoystickEvent.hpp"


#include "RPiForklift.hpp"
#include "RMotorDriver.hpp"
#include "RPiServo.hpp"
#include "RNetServer.hpp"
#include "RVidStream.hpp"


#include "ForkliftConstants.h"

// For command handling
using CommandKey = std::pair<EVENT_COMMAND_TYPE, EVENT_DATA_TYPE>;
using CommandHandler = std::function<void(const RControlEvent &)>;

/**
 * @brief Main object class for the Forklift project
 * 
 */
class RForkliftManager
{
    private:
    RMotorDriver * m_driver;
    RPiForklift * m_forklift;

    cv::VideoCapture m_camera;
    RVidStream * m_stream;

    RNetServer m_server;

    std::vector<RControlEvent> m_commandQueue;
    std::map<CommandKey, CommandHandler> m_commandHandlers;

    bool m_flagRun = false;
    bool m_flagAutoAvailable = true;

    std::string m_frontCamIP;
    int m_frontCamPort;

    void init_kbhit();
    void end_kbhit();

    void registerCommands();
    void handleCommand(const RControlEvent &cmd);

    void com_setAnalog(int origin, std::vector<int> values);
    void com_setCommand(int origin, std::vector<std::string> values);
    void com_getCommand(int origin, std::vector<std::string> values);
    void com_setDigital(int origin, std::vector<bool> values);

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