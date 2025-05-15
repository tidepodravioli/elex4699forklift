#pragma once

#define _USE_MATH_DEFINES

#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>
#include <cmath>

#include "RCoordinateHelper.hpp"
#include "RMotorWriter.hpp"

#define MAX_AUTO_SPEED 150.0f
#define ANGLE_GAIN 80.0f
#define POINT_DISTANCE_THRESHOLD 100.0f
#define DRIVE_CORRECTION_COOLDOWN 20


/**
 * @brief Provides automatic driving of the robot based on a destination or a desired heading
 * @details RAutoPilot uses RCoordinateHelper as a means of driving to points on the map. It 
 * uses the location of the robot, as given by the helper, to determine a straight-ish path to
 * a destination point.
 */

class RAutoPilot : public RMotorWriter
{
    private:
    RCoordinateHelper * m_helper; ///< Provides the positional information of the robot on the map

    public:
    /**
     * @brief 
     * @param driver The driver object to manipulate (MUST BE INITIALIZED)
     * @param helper The coordinate provider (MUST BE INITALIZED AND READY)
     */
    RAutoPilot(RMotorWriter &driver, RCoordinateHelper &helper);

    /**
     * @brief Drives the robot to a given point of the coordinate grid
     * 
     * @param point The point on the coordinate grid to drive to (relative to the x-y origin of the Mat)
     */
    void driveToPoint(cv::Point2i point);

    /**
     * @brief Orients the robot to match the given angle without translating
     * 
     * @param angle The angle to match (in radians)
     */
    void orientRobot_r(float angle);

    /**
     * @brief Orients the robot to match the given angle without translating
     * 
     * @param angle The angle to match (in degrees)
     */
    void orientRobot_d(float angle);

    /**
     * @brief Drives to every point in the given path
     * 
     * @param path Collection of points to drive to
     */
    void drivePath(std::vector<cv::Point2i> path);
};