#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <string>

#include "ForkliftConstants.h"

using namespace cv;
using namespace std;

class RAutoFork
{
    private:
    Mat m_cameraMatrix, m_distCoeffs;

    public:
    RAutoFork();

    bool importCalibration(string fileName = CAMERA_CALIBRATION);

    float getDistanceClosestTag(Mat &im);
};