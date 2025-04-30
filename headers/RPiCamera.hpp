#pragma once

#include <opencv2/opencv.hpp>
#include <thread>
#include <string>
#include <mutex>
#include <sstream>
#include "stdlib.h"
#include "stdio.h"

using namespace cv;
using namespace std;

class RPiCamera
{
    private:
    // ====== CAMERA STUFF =======
    VideoCapture m_camera;
    Mat m_currentFrame;
    mutex * m_frameAccess;
    bool m_flagOpen = false;

    void getFrameT();

    // ====== NETWORKING STUFF ======
    bool m_flagSendFrame = false;
    bool m_flagConnected = false;
    bool m_flagConnecting = false;
    void startServer(string IPaddr, int port);
    void sendFrame(VideoWriter &writer);
    

    public:
    /**
     * @brief Construct a new RPiCamera object
     * 
     */
    RPiCamera(int index, int apiPreference);

    /**
     * @brief Gets the current frame of the camera
     * 
     * @param frame The frame as a cv::Mat
     * @return true if the frame isn't empty
     * @return false otherwise
     */
    bool getFrame(Mat &frame);

    /**
     * @brief Starts a gstreamer stream at the given socket
     * Uses a new thread. Will only start one instance.
     *
     * @param IPaddr The IP address to use
     * @param port The port for the socket being used
     * @return true if the connection has been established
     * @return false otherwise
     */
    bool startStream(string IPaddr, int port);

    /**
     * @brief Ends the current stream
     * 
     */
    void endStream();
};