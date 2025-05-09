#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "stdio.h"

#include "ForkliftConstants.h"

using namespace cv;
using namespace std;

class RPiCamera : public VideoCapture
{
    private:
    public:
    /**
     * @brief Construct a new RPiCamera object
     * 
     */
    RPiCamera(int index = 0, int apiPreference = CAP_V4L2) : VideoCapture(index, apiPreference) {}

    bool importCalibration(string filename = CAMERA_CALIBRATION);

    float getDistanceClosestTag();

    Vec3d getTranslationClosestTag();
};