#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <iostream>

#include "../../../CLIENT/headers/RArUcoReader.hpp"
#include "../../../CLIENT/headers/RArUcoTag.hpp"
#include "../../../CLIENT/headers/RPiCamera.hpp"


using namespace std;
using namespace cv;

class ArUcoTest
{
    private:
    Mat m_cameraMatrix, m_distCoeffs;
    Vec3f updateTranslation(const Vec3d& raw);

    public:
    ArUcoTest();

    void start();
};