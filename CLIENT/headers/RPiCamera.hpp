#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "stdio.h"

#include "../../shared/headers/ForkliftConstants.h"
#include "RArUcoReader.hpp"
#include "RArUcoTag3.hpp"

using namespace std;

/**
 * @brief Provides an interface to the Raspberry Pi camera, with depth detection
 * @details RPiCamera inherits from cv::VideoCapture to provide classic Mat frame
 * based image getting, but also integrates the aruco library to provide depth 
 * information and tag reading.
 * 
 */
class RPiCamera : public cv::VideoCapture
{
    private:
    cv::Mat m_cameraMatrix, m_distCoeffs;

    RArUcoReader m_reader;

    public:
    /**
     * @brief Constructs a new RPiCamera video stream
     * 
     * @param index The index the camera is associated with
     * @param apiPreference The API to use to connect to the camera
     */
    RPiCamera(int index = 0, int apiPreference = cv::CAP_V4L2);

    /**
     * @brief Imports a prepared camera calibration (needed for depth and ArUco tag detection)
     * 
     * @param filename Location of the file to use for camera calibration
     * @return true if the import was successful
     * @return false if the import failed or the file wasn't found
     */
    bool importCalibration(string filename = CAMERA_CALIBRATION);

    /**
     * @brief Gets a vector of the detected tags in the next frame, ordered from closest to farthest
     * 
     * @param valid if tags were found in the image
     * @return vector<RArUcoTag3> The detected tags in the image, ordered from closest to farthest
     */
    vector<RArUcoTag3> getClosestTags(bool &valid);

    /**
     * @brief Get the distance from the closest tag in the image
     * 
     * @param distance The distance from the closest tag
     * @return true if a tag was found
     * @return false if a tag wasn't found
     */
    bool getDistanceClosestTag(float &distance);

    /**
     * @brief Gets the translation vector of the closest tag from the center point of the camera
     * 
     * @param trans The translation vector
     * @return true if a tag was found
     * @return false if a tag wasn't found
     */
    bool getTranslationClosestTag(cv::Vec3d &trans);
};