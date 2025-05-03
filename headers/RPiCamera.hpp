#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "stdio.h"

using namespace cv;
using namespace std;

class RPiCamera
{
    private:
    VideoCapture m_camera;
    Mat m_currentFrame;
    bool m_flagOpen = false;
    

    public:
    /**
     * @brief Construct a new RPiCamera object
     * 
     */
    RPiCamera(int index = 0, int apiPreference = CAP_V4L2);

    /**
     * @brief Gets the current frame of the camera
     * 
     * @param frame The frame as a cv::Mat
     * @return true if the frame isn't empty
     * @return false otherwise
     */
    bool getFrame(Mat &frame);

    bool isOpened();

    VideoCapture* getVidCapPtr();
};