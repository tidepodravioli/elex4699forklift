#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <iostream>

#include "../../../CLIENT/headers/RArUcoReader.hpp"
#include "../../../CLIENT/headers/RArUcoTag.hpp"
#include "../../../CLIENT/headers/RPiCamera.hpp"
#include "../../../CLIENT/headers/RCoordinateHelper.hpp"


using namespace std;
using namespace cv;

class ArUcoTest
{
    private:
    Mat m_cameraMatrix, m_distCoeffs;

    public:
    ArUcoTest();

    void start();
    bool importCalibration(string fileName);
    double getDistanceToClosestMarker(cv::Mat& frame, cv::Ptr<cv::aruco::Dictionary> dictionary);
};