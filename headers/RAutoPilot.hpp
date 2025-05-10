#pragma once
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>
#include <cmath>

#include "RCoordinateHelper.hpp"
#include "RMotorDriver.hpp"

#define MAX_AUTO_SPEED 150.0f
#define ANGLE_GAIN 80.0f
#define POINT_DISTANCE_THRESHOLD 100.0f
#define DRIVE_CORRECTION_COOLDOWN 20

using namespace cv;

class RAutoPilot : public RMotorDriver
{
    private:
    RMotorDriver * m_driver;
    RCoordinateHelper * m_helper;

    public:
    RAutoPilot(RMotorDriver &driver, RCoordinateHelper &helper);

    void driveToPoint(Point2i point);

    void orientRobot(float angle);

    void drivePath(vector<Point2i> path);
};