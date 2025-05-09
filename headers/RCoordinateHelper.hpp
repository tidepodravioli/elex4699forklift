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
#include "RArUcoTag3.hpp"
#include "RPointVect.h"

#include "ForkliftConstants.h"

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

    bool m_flagRobotFound = false;
    RArUcoReader m_aruco;
    RPointVect m_robot;

    CClient m_camera;

    int m_channel;

    string m_commandGet = "";

    bool m_flagGetFrame = false;
    mutex * m_mutexCurrentFrame;
    void getFrame_t();

    bool m_flagRefresh;

    public:
    /**
     * @brief Creates an RCoordinateHelper using the given camera channel
     * 
     * @param cameraChannel Channel to find camera on
     * @param refresh Whether or not to call refreshRobot() before getting the robots position
     */
    RCoordinateHelper(int cameraChannel = OVERHEAD_CAMERA_CHANNEL, bool refresh = false);

    /**
     * @brief Starts getting live frames from the camera
     * 
     */
    void startFrameGetter();

    /**
     * @brief Stops getting frames from the camera
     * 
     */
    void stopFrameGetter();
    
    /**
     * @brief Refreshes the position and angle of the robot on screen
     * 
     */
    void refreshRobot();

    /**
     * @brief Gets a frame of the overhead camera for evaluation
     * 
     * @param im The cv::Mat to store the frame on
     * @return true if the frame isn't empty,
     * @return false otherwise
     */
    bool getFrame(Mat &im);

    /**
     * @brief 
     * 
     * @return RPointVect 
     */
    RPointVect locateRobot();

    bool robotFound();

    float getRobotAngle_r();

    float getPointAngle_r(Point2i destination);

    float getRobotAngle_d();

    float getPointAngle_d(Point2i destination);

    Point2i getRobotCoords();

    Point2i getTagCoords(RArUcoTag3 tag);
};