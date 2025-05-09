#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <iostream>

#include "../../../headers/RArUcoReader.hpp"
#include "../../../headers/RArUcoTag.hpp"
#include "../../../headers/RPiCamera.hpp"


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