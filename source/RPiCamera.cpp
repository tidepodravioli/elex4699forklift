#include "../headers/RPiCamera.hpp"

RPiCamera::RPiCamera(int index, int apiPreference)
{
    m_camera.open(index, apiPreference);
    m_flagOpen = m_camera.isOpened();
}


bool RPiCamera::getFrame(Mat &frame)
{
    if(m_flagOpen)
    {
        Mat _frame;
        m_camera >> _frame;

        if(!_frame.empty())
        {
            frame = _frame;
            return true;
        }
        else return false;
    }
    else return false;
}

bool RPiCamera::isOpened()
{
    m_flagOpen = m_camera.isOpened();
    return m_flagOpen;
}

void RPiCamera::getVidCapObj(VideoCapture &obj)
{
    obj = m_camera;
}