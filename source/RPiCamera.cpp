#include "../headers/RPiCamera.hpp"

RPiCamera::RPiCamera(int index, int apiPreference)
{
    m_camera.open(index, apiPreference);
    m_flagOpen = m_camera.isOpened();

    m_frameAccess = new mutex();
}

void RPiCamera::_getFrame()
{
    m_camera >> m_currentFrame;
}


bool RPiCamera::getFrame(Mat &frame)
{
    _getFrame();
    frame = m_currentFrame;
    return m_flagOpen;
}

bool RPiCamera::startStream(string IPaddr, int port)
{
    stringstream pipeline("appsrc ! videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=ultrafast ! rtph264pay config-interval=1 pt=96 ! udpsink "); 
    pipeline << "host=";
    pipeline << IPaddr;
    pipeline << " port=";
    pipeline << port;
    
    VideoWriter writer(pipeline.str(), CAP_GSTREAMER, 0, 30, Size(640, 480), true);
    if(writer.isOpened())
    {
        m_flagSendFrame = true;

        thread framesender_t(&RPiCamera::sendFrame, writer);
        framesender_t.detach();

        return true;
    }
    else 
    {
        cout << "RPiCamera : network writer not opened.";
        return false;
    }
}

void RPiCamera::sendFrame(VideoWriter &writer)
{
    while(m_flagSendFrame)
    {
        m_camera >> m_currentFrame;
        writer.write(m_currentFrame);
    }
}