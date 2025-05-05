#include "../headers/RCoordinateHelper.hpp"

RCoordinateHelper::RCoordinateHelper(VideoCapture &camera)
{
    m_camera = &camera;
    m_currentFrame = nullptr;
}

void RCoordinateHelper::nextFrame(Mat &frame)
{
    if(m_camera != nullptr) m_currentFrame = &frame;
}

bool RCoordinateHelper::update()
{
    if(m_camera != nullptr)
    {

    }
    else if(m_camera->isOpened())
    {
        Mat frame;
        m_camera->read(frame);

        if(!frame.empty())
        {
            
        }
    }
    else return false;
}

RPointVect RCoordinateHelper::locateRobot()
{
    
}

float RCoordinateHelper::getRobotAngle()
{

}

float RCoordinateHelper::getPointAngle(Point2i destination)
{
    
}
