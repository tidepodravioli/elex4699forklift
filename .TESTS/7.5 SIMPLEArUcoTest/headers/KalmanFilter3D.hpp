#pragma once

#include <opencv2/video/tracking.hpp>
#include <opencv2/core.hpp>

class KalmanFilter3D {
public:
    KalmanFilter3D(float processNoise = 1e-2, float measurementNoise = 1e-1,
                   float maxJump = 100.0f, float maxDelta = 50.0f);

    cv::Vec3f update(const cv::Vec3f& rawMeasurement);

private:
    cv::KalmanFilter kalman;
    cv::Mat state;      // [x, y, z, dx, dy, dz]
    cv::Mat meas;       // [x, y, z]
    bool initialized = false;

    float maxReasonableJump;
    float maxDeltaPerFrame;
    cv::Vec3f lastFiltered;
};
