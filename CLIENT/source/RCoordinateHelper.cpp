#include "../headers/RCoordinateHelper.hpp"

using namespace std; 

RCoordinateHelper::RCoordinateHelper(int cameraChannel, bool refresh) : CClient()
{
    m_channel = cameraChannel;
    stringstream command;
    command << "G " << m_channel;

    m_commandGet = command.str();

    m_flagRefresh = refresh;
}

RCoordinateHelper::~RCoordinateHelper()
{
    close_socket();
}

bool RCoordinateHelper::getFrame(cv::Mat &im)
{
    im = m_currentFrame;

    return !im.empty();
}

bool RCoordinateHelper::refreshRobot()
{
    tx_str(m_commandGet); // ask for the next frame
    this_thread::sleep_for(chrono::milliseconds(30)); // wait a little bit for the response
    rx_im(m_currentFrame); // receive the frame

    if(!m_currentFrame.empty())
    {
        std::vector<RArUcoTag> tags = m_aruco.getTags(m_currentFrame);
        for(RArUcoTag tag : tags)
        {
            if(tag.getID() == ROBOT_ARUCO_ID)
            {
                m_robot.coord = tag.getCenter();
                m_robot.angle = tag.getAngle_r();
                m_flagRobotFound = true;
            }
            else m_flagRobotFound = false;
        }

        return true;
    }
    else m_flagRobotFound = false;

    return !m_currentFrame.empty();
}

    

RPointVect RCoordinateHelper::locateRobot()
{
    if(m_flagRefresh) refreshRobot();
    return m_robot;
}

bool RCoordinateHelper::robotFound()
{
    if(m_flagRefresh) refreshRobot();
    return m_flagRobotFound;
}

float RCoordinateHelper::getRobotAngle_r()
{
    if(m_flagRefresh) refreshRobot();
    return m_robot.angle;
}

float RCoordinateHelper::getPointAngle_r(cv::Point2i destination)
{
    if(m_flagRefresh) refreshRobot();
    //get slope of line between robot and destination
    const float rise = (float)destination.y - m_robot.coord.y;
    const float run = (float)destination.x - m_robot.coord.x;

    return atan2(rise, run);
}

float RCoordinateHelper::getRobotAngle_d()
{
    return m_robot.angle * 180.0f / CV_PI;
}

float RCoordinateHelper::getPointAngle_d(cv::Point2i destination)
{
    return getPointAngle_r(destination) * 180.0f / CV_PI;
}

cv::Point2i RCoordinateHelper::getRobotCoords()
{
    if(m_flagRefresh) refreshRobot();
    return cv::Point2i(m_robot.coord.x, m_robot.coord.y);
}

cv::Point2i RCoordinateHelper::getTagCoords(RArUcoTag3 tag)
{
    if(m_flagRefresh) refreshRobot();
    const cv::Size2i frameSize = m_currentFrame.size();

    const float widthFactor = frameSize.width / ARENA_WIDTH; 
    const float heightFactor = frameSize.height / ARENA_HEIGHT;

    const cv::Vec3d tagTrans = tag.getTrans();
    const float cam_cx = tagTrans[0];
    const float cam_cz = tagTrans[2];

    const float robot_cx = m_robot.coord.x / widthFactor;
    const float robot_cy = m_robot.coord.y / heightFactor;

    float x0 = robot_cx + cam_cz * cos(m_robot.angle) - cam_cx * sin(m_robot.angle);
    float y0 = robot_cy + cam_cz * sin(m_robot.angle) + cam_cx * cos(m_robot.angle);

    x0 *= widthFactor;
    y0 *= heightFactor;

    return cv::Point2i(x0, y0);
}
