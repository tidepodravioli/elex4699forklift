#include "KalmanFilter3D.hpp"

using namespace cv;

KalmanFilter3D::KalmanFilter3D(float processNoise, float measurementNoise,
                               float maxJump, float maxDelta)
    : maxReasonableJump(maxJump), maxDeltaPerFrame(maxDelta) {

    kalman.init(6, 3); // 6 state variables (x,y,z + dx,dy,dz), 3 measurements

    // Transition matrix (A)
    kalman.transitionMatrix = (Mat_<float>(6, 6) <<
        1, 0, 0, 1, 0, 0,
        0, 1, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 1,
        0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 1);

    setIdentity(kalman.measurementMatrix);              // H
    setIdentity(kalman.processNoiseCov, Scalar(processNoise));   // Q
    setIdentity(kalman.measurementNoiseCov, Scalar(measurementNoise)); // R
    setIdentity(kalman.errorCovPost, Scalar(1));        // P

    state = Mat::zeros(6, 1, CV_32F);
    meas = Mat::zeros(3, 1, CV_32F);
}

Vec3f KalmanFilter3D::update(const Vec3f& rawMeasurement) {
    if (!initialized) {
        // First measurement initializes state
        state.at<float>(0) = rawMeasurement[0];
        state.at<float>(1) = rawMeasurement[1];
        state.at<float>(2) = rawMeasurement[2];
        kalman.statePost = state.clone();
        initialized = true;
        lastFiltered = rawMeasurement;
        return rawMeasurement;
    }

    Mat prediction = kalman.predict();
    Vec3f predicted(
        prediction.at<float>(0),
        prediction.at<float>(1),
        prediction.at<float>(2));

    Vec3f deltaToPred = rawMeasurement - predicted;

    Vec3f filtered;
    if (norm(deltaToPred) < maxReasonableJump) {
        // Accept measurement
        meas.at<float>(0) = rawMeasurement[0];
        meas.at<float>(1) = rawMeasurement[1];
        meas.at<float>(2) = rawMeasurement[2];

        Mat estimated = kalman.correct(meas);
        filtered = Vec3f(
            estimated.at<float>(0),
            estimated.at<float>(1),
            estimated.at<float>(2));
    } else {
        // Reject measurement, rely on prediction
        filtered = predicted;
    }

    // Optionally smooth out visual jitter
    Vec3f frameDelta = filtered - lastFiltered;
    if (norm(frameDelta) > maxDeltaPerFrame) {
        filtered = lastFiltered + frameDelta * (maxDeltaPerFrame / norm(frameDelta));
    }

    lastFiltered = filtered;
    return filtered;
}
