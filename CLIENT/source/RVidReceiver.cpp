#include "../headers/RVidReceiver.hpp"

RVidReceiver::RVidReceiver(bool debug)
{
    m_debug = debug;
}

void RVidReceiver::listen(int port)
{
    const string pipeline = getPipeline(port);

    m_camera = new VideoCapture(pipeline, CAP_GSTREAMER);

    if(m_camera->isOpened())
    {
        m_flagConnected = true;
        if(m_debug) cout << "RVidReceiver : Receiving video" << endl;
    }
    else
    {
        m_flagConnected = false;
        if(m_debug) cout << "RVidReceiver : Connection failed" << endl;
    }
}

string RVidReceiver::getPipeline(int port)
{
    stringstream pipeline;
    pipeline << "udpsrc port=";
    pipeline << port;
    pipeline << " caps=\"application/x-rtp, media=video, encoding-name=H264, payload=96\" ! rtph264depay ! avdec_h264 ! videoconvert ! appsink";

    return pipeline.str();
}

bool RVidReceiver::getFrame(Mat &im)
{
    if(m_flagConnected)
    {
        *m_camera >> im;
        return im.empty();
    }
    else return false;
}