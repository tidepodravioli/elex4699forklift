#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <sstream>
#include <vector>
#include <math.h>

#include "../shared/headers/ext/Client.h"
#include "RArUcoReader.hpp"
#include "RArUcoTag.hpp"
#include "RPointVect.h"

#define ROBOT_ARUCO_ID 188
#define OVERHEAD_CAMERA_CHANNEL 1
#define FRAME_GETTER_TIMEOUT_MS 20

using namespace cv;
using namespace std;

/**
 * @brief Interface to the overhead bird's eye view camera that
 * gives the angle and coordinates of the robot, as well as the
 * relative angle of the robot to a point on the map
 * 
 */
class RCoordinateHelper : public CClient
{
    private:
    Mat m_currentFrame;

    RArUcoReader m_aruco;
    RPointVect m_robot;

    CClient m_camera;

    int m_channel;

    string m_commandGet = "";

    bool m_flagGetFrame = false;
    mutex * m_mutexCurrentFrame;
    void getFrame_t();

    public:
    RCoordinateHelper(int cameraChannel = OVERHEAD_CAMERA_CHANNEL);

    void startFrameGetter();

    void stopFrameGetter();
    
    void refreshRobot();

    bool getFrame(Mat &im);

    RPointVect locateRobot();
    float getRobotAngle();

    float getPointAngle(Point2i destination);

    
};