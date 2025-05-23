#pragma once

#include <iostream>
#include <chrono>
#include <regex>
#include <string>
#include <conio.h>
#include <thread>
#include <opencv2/opencv.hpp>

#include "ext/getstuff.h"
#include "ext/CControl.h"

#include "RNetClient.hpp"
#include "RVidReceiver.hpp"
#include "RPiCamera.hpp"
#include "RCoordinateHelper.hpp"
#include "RMotorWriter.hpp"
#include "RAutoPilot.hpp"
#include "RDraw.hpp"

#define E4618_IPADDR_REGEX "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$" ///< IP address regex



class RForkliftClient
{
private:
    CControl m_serial;
    RNetClient m_network;
    RDraw * m_ui;
    RPiCamera m_camstream;
    RMotorWriter * m_writer;
    RAutoPilot * m_autopilot;
    RCoordinateHelper m_helper;

    std::chrono::steady_clock::time_point m_lastEvent;
    cv::Mat m_currentFrame;

    // Connection state flags
    bool m_flagConnected = false;
    bool m_flagSerialConnected = false;
    bool m_flagFrontCamConnected = false;
    bool m_flagArenaCamConnected = false;

    // Settings flags
    bool m_flagManualAvailable = true;
    bool m_flagFrontCamNeeded = true;
    bool m_flagArenaCamNeeded = true;

    // Robot state flags
    bool m_flagAutoMode = false;
    bool m_flagSlowMode = false;
    bool m_flagRun = false;

    //UI flags
    bool m_flagThreadedUIrefresh = false;
    bool m_flagArenaCamShow = false;

    // Last socket
    std::string m_lastIP;
    int m_lastPort = -1;

    
    void cli_getSocket();
    void cli_getCControl();
    void cli_startClient();

    void proc_client();
    /**
     * @brief Gets the current state of the controller and sends it over the network for processing by the server.
     * 
     */
    void proc_manual();

    void proc_auto();

    void cli_IOTest();
    void gui_UITest();
    void cli_streamTest();
    void cli_antirafTest();
    void cli_directCommandTest();
    
    void cli_showMenu();
    void cli_saveSettings();
    void cli_loadSettings();
    void cli_loadSettingsOnOpen();
    void cli_settings();

    void start_front_cam();
    void start_ui(cv::Mat &init_arena);
    void stop_ui();

    void t_showFrontCam();
    void t_showArenaCam();
    void t_refreshUI();
public:
    RForkliftClient() {}

    void start();
};