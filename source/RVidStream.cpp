#include "../headers/RVidStream.hpp"

bool RVidStream::target(string IPaddr, int port)
{
    m_flagConnecting = true;

    thread server_t(&RVidStream::startServer_t, this, IPaddr, port);
    server_t.detach();

    while(m_flagConnecting);
    return m_flagConnected;
}

void RVidStream::startServer_t(string IPaddr, int port)
{
    stringstream pipeline("appsrc ! videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=ultrafast ! rtph264pay config-interval=1 pt=96 ! udpsink "); 
    pipeline << "host=";
    pipeline << IPaddr;
    pipeline << " port=";
    pipeline << port;

    VideoWriter writer(pipeline.str(), CAP_GSTREAMER, 0, 30, Size(640, 480));
    if(writer.isOpened())
    {
        m_flagConnected = true;
        m_flagConnecting = false;

        m_writer = &writer;
        if(m_debug) cout << "RPiCamera : Network writer opened successfully." << endl;
    }
    else 
    {
        m_flagConnected = false;
        m_flagConnecting = false;
        if(m_debug) cout << "RPiCamera : Network writer not opened." << endl;
    }
}

void RVidStream::sendFrame(Mat &frame)
{
    m_writer->write(frame);
}

bool RVidStream::stream(VideoCapture &source)
{
    if(source.isOpened() && m_flagConnected)
    {
        m_flagStream = true;
        thread streamer_t(&RVidStream::stream_t, this, source);
        streamer_t.detach();

        return true;
    }
    else return false;
}

bool RVidStream::stream(RPiCamera &camera)
{
    VideoCapture * _camera = camera.getVidCapPtr();

    return stream(*_camera);
}



void RVidStream::stream_t(VideoCapture &source)
{
    while(m_flagStream)
    {
        Mat frame;
        source >> frame;

        if(!frame.empty())
        {
            m_writer->write(frame);
        }
    }
}

void RVidStream::stopStream()
{
    m_flagStream = false;
}