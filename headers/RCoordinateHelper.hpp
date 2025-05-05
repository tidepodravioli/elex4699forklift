#include <opencv2/opencv.hpp>

#include "RArUcoReader.hpp"
#include "RArUcoTag.hpp"
#include "RPointVect.h"

#define ROBOT_ARUCO_ID 188

using namespace cv;


/**
 * @brief Interface to the overhead bird's eye view camera that
 * gives the angle and coordinates of the robot, as well as the
 * relative angle of the robot to a point on the map
 * 
 */
class RCoordinateHelper
{
    private:
    VideoCapture * m_camera = nullptr;
    Mat * m_currentFrame = nullptr;

    RArUcoTag * m_robot;

    public:
    RCoordinateHelper(VideoCapture &camera);
    RCoordinateHelper(Mat &init_frame);

    void nextFrame(Mat &frame);

    bool update();

    RPointVect locateRobot();
    float getRobotAngle();

    float getPointAngle(Point2i destination);

    
};