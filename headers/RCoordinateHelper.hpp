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
 * @details RCoordinate helper provides a means to determine the
 * position of the robot on the map, based on its pixel position
 * relative to the overhead camera. It does this by polling a
 * camera communicating over Craig's Client/Server architechture.
 * Whenever the position is needed, refreshRobot() must be called.
 * This function makes a working copy of the current frame and
 * performs the operations necessary to provide the position and
 * angle of the robot. After updating the view of the robot, we
 * are now able to provide concurrent information regarding its
 * position and angle in a given instant of time.
 * 
 * Example setup :
 * @code 
 * RCoordinateHelper helper(1, true);
 * helper.connect_socket("192.168.0.101", 5008);
 * helper.startFrameGetter();
 * @endcode
 */
class RCoordinateHelper : public CClient
{
    private:
    Mat m_currentFrame; ///< Represents the current working frame that is being evaluated

    bool m_flagRobotFound = false; ///< If the robot was found the last time its position was updated
    RArUcoReader m_aruco; ///< The tag representing the robot's location on the map
    RPointVect m_robot; ///< The location and rotation of the robot's tag

    int m_channel; ///< The channel the camera is on

    string m_commandGet = ""; ///< The command to be sent over TCP to get the frames of the camera

    bool m_flagGetFrame = false; ///< If the frame getter should be running or not
    mutex * m_mutexCurrentFrame; ///< Mutex that protexts m_currentFrame

    /**
     * @brief Polls the network camera for frames. Runs in a separate thread.
     * 
     */
    void getFrame_t();

    bool m_flagRefresh; ///< Whether or not to refresh the robot whenever a function that requires or gets its position is called

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
     * @brief Returns the robot's angle and position as an RPointVect object
     * 
     * @return RPointVect 
     */
    RPointVect locateRobot();

    /**
     * @brief Whether or not the robot was found during the last refresh
     * 
     * @return true if the robot was found
     * @return false otherwise
     */
    bool robotFound();

    /**
     * @brief Gets the angle of the robot relative to the camera
     * 
     * @return float The angle of the robot in radians
     */
    float getRobotAngle_r();

    /**
     * @brief Gets the angle relative to the line made by the robot's position and the given destination
     * 
     * @param destination The point that the angle is made with
     * @return float The angle made by the line in radians
     */
    float getPointAngle_r(Point2i destination);

    /**
     * @brief Gets the angle of the robot relative to the camera
     * 
     * @return float The angle of the robot in degrees
     */
    float getRobotAngle_d();

    /**
     * @brief Gets the angle relative to the line made by the robot's position and the given destination
     * 
     * @param destination The point that the angle is made with
     * @return float The angle made by the line in degrees
     */
    float getPointAngle_d(Point2i destination);

    /**
     * @brief Gets robot's coordinates on the arena
     * 
     * @return Point2i 
     */
    Point2i getRobotCoords();

    /**
     * @brief Gets the coordinate of an RArUcoTag3 seen by the front camera is terms of the arena's coordinate system
     * 
     * @param tag The tag to find on the plane
     * @return Point2i The location of the tag in the planar space
     */
    Point2i getTagCoords(RArUcoTag3 tag);
};