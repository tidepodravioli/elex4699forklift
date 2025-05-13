#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <chrono>

#include "RPiCamera.hpp"
#include "RCoordinateHelper.hpp"
#include "ForkliftConstants.h"

class RAutoFork
{
    private:
    RPiCamera * m_camera;
    RCoordinateHelper * m_helper;
    Vec3d m_closest_tag_translation;
    double m_closest_tag_angle;
    std::chrono::seconds m_backupTime = std::chrono::seconds(FORKLIFT_BACKUP_TIME);
    bool valid;

    public:
    RAutoFork(RPiCamera &camera, RCoordinateHelper &helper);

    void dock();

    void pickup();
};