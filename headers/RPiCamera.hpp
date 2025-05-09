#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "stdio.h"

#include "ForkliftConstants.h"
#include "RArUcoTag3.hpp"

using namespace cv;
using namespace std;

class RPiCamera : public VideoCapture
{
    private:
    Mat m_cameraMatrix, m_distCoeffs;

    cv::Ptr<cv::aruco::Dictionary> m_dictionary;

    public:
    /**
     * @brief Construct a new RPiCamera object
     * 
     */
    RPiCamera(int index = 0, int apiPreference = CAP_V4L2);

    bool importCalibration(string filename = CAMERA_CALIBRATION);

    vector<RArUcoTag3> getClosestTags(bool &valid);

    bool getDistanceClosestTag(float &distance);

    bool getTranslationClosestTag(Vec3d &trans);
};