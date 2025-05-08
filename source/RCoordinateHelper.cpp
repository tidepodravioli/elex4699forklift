#include "../headers/RCoordinateHelper.hpp"

RCoordinateHelper::RCoordinateHelper(int cameraChannel) : CClient()
{
    m_channel = cameraChannel;
    stringstream command;
    command << "G " << m_channel;

    m_commandGet = command.str();
}

void RCoordinateHelper::startFrameGetter()
{
    if(!m_flagGetFrame)
    {
        m_flagGetFrame = true;
        m_mutexCurrentFrame = new mutex();
    
        thread frameget_t(&RCoordinateHelper::getFrame_t, this);
        frameget_t.detach();
    }
}

void RCoordinateHelper::stopFrameGetter()
{
    m_flagGetFrame = false;
}

void RCoordinateHelper::getFrame_t()
{
    while(m_flagGetFrame)
    {
        tx_str(m_commandGet);
        
        m_mutexCurrentFrame->lock();
        rx_im(m_currentFrame);
        m_mutexCurrentFrame->unlock();

        this_thread::sleep_for(chrono::milliseconds(FRAME_GETTER_TIMEOUT_MS));
    }
}

bool RCoordinateHelper::getFrame(Mat &im)
{
    m_mutexCurrentFrame->lock();
    im = m_currentFrame.clone();
    m_mutexCurrentFrame->unlock();

    return !im.empty();
}

void RCoordinateHelper::refreshRobot()
{
    m_mutexCurrentFrame->lock();
    Mat frame = m_currentFrame.clone();
    m_mutexCurrentFrame->unlock();

    vector<RArUcoTag> tags = m_aruco.getTags(frame);
    for(RArUcoTag tag : tags)
    {
        if(tag.getID() == ROBOT_ARUCO_ID)
        {
            m_robot.coord = tag.getCenter();
            m_robot.angle = tag.getAngle();
            m_flagRobotFound = true;
            return;
        }
        else m_flagRobotFound = false;
    }
}

RPointVect RCoordinateHelper::locateRobot()
{
    return m_robot;
}

bool RCoordinateHelper::robotFound()
{
    return m_flagRobotFound;
}

float RCoordinateHelper::getRobotAngle()
{
    return m_robot.angle;
}

float RCoordinateHelper::getPointAngle(Point2i destination)
{
    //get slope of line between robot and destination
    const float rise = (float)destination.y - m_robot.coord.y;
    const float run = (float)destination.x - m_robot.coord.x;

    return atan2(rise, run);
}

Point2i RCoordinateHelper::getRobotCoords()
{
    return Point2i(m_robot.coord.x, m_robot.coord.y);
}
