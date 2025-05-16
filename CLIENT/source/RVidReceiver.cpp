#include "../headers/RVidReceiver.hpp"

using namespace std;

RVidReceiver::RVidReceiver(bool debug)
{
    m_debug = debug;
}

bool RVidReceiver::listen(int port)
{
    const string pipeline = getPipeline(port);

    open(pipeline, cv::CAP_GSTREAMER);

    if(isOpened())
    {
        m_flagConnected = true;
        if(m_debug) cout << "RVidReceiver : Receiving video" << endl;
        return true;
    }
    else
    {
        m_flagConnected = false;
        if(m_debug) cout << "RVidReceiver : Connection failed" << endl;
        return false;
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

bool RVidReceiver::getFrame(cv::Mat &im)
{
    if(m_flagConnected)
    {
        read(im);
        return !im.empty();
    }
    else return false;
}