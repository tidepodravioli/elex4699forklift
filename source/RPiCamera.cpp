#include "../headers/RPiCamera.hpp"

RPiCamera::RPiCamera(int index, int apiPreference)
{
    m_camera.open(index, apiPreference);
    m_flagOpen = m_camera.isOpened();

    m_frameAccess = new mutex();

    thread framegetter_t(&RPiCamera::getFrameT, this);
    framegetter_t.detach();
}

void RPiCamera::getFrameT()
{
    while(m_flagOpen)
    {
        m_frameAccess->lock();
        m_camera >> m_currentFrame;
        m_frameAccess->unlock();

        m_flagOpen = m_camera.isOpened();
    }
}


bool RPiCamera::getFrame(Mat &frame)
{
    m_frameAccess->lock();
    frame = m_currentFrame;
    m_frameAccess->unlock();

    return !frame.empty();
}

bool RPiCamera::startStream(string IPaddr, int port)
{
    m_flagConnecting = true;

    thread server_t(&RPiCamera::startServer, this, IPaddr, port);
    server_t.detach();

    while(m_flagConnecting);
    return m_flagConnected;
}

void RPiCamera::startServer(string IPaddr, int port)
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
        m_flagConnected = true;
        m_flagConnecting = false;

        sendFrame(writer);
    }
    else 
    {
        m_flagConnected = false;
        m_flagConnecting = false;
        cout << "RPiCamera : network writer not opened.";
    }
}

void RPiCamera::sendFrame(VideoWriter &writer)
{
    while(m_flagSendFrame)
    {
        writer.write(m_currentFrame);
    }
}