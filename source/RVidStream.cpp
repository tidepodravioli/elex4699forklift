#include "../headers/RVidStream.hpp"

RVidStream::RVidStream(bool debug)
{
    m_debug = debug;
}

bool RVidStream::target(string IPaddr, int port)
{
    const string pipeline = getPipeline(IPaddr, port);
    m_writer = new VideoWriter(pipeline, CAP_GSTREAMER, 0, 30, Size(640, 480));
    if(m_writer->isOpened())
    {
        m_flagConnected = true;

        if(m_debug) cout << "RPiCamera : Network writer opened successfully." << endl;
    }
    else 
    {
        m_flagConnected = false;
        if(m_debug) cout << "RPiCamera : Network writer not opened." << endl;
    }

    return m_flagConnected;
}

void RVidStream::sendFrame(Mat &frame)
{
    m_writer->write(frame);
    cout << frame.size() << endl;
}

bool RVidStream::stream(VideoCapture &source)
{
    if(source.isOpened() && m_flagConnected)
    {
        m_flagStream = true;
        thread streamer_t(&RVidStream::stream_t, this, ref(source));
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

string RVidStream::getPipeline(string IPaddr, int port)
{
    stringstream pipeline;
    pipeline << "appsrc caps=video/x-raw,format=RGB,width=640,height=480,framerate=30/1 ! videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=ultrafast ! rtph264pay config-interval=1 pt=96 ! udpsink "; 
    pipeline << "host=";
    pipeline << IPaddr;
    pipeline << " port=";
    pipeline << port;

    return pipeline.str();
}