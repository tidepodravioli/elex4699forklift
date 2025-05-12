#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>

using namespace std;
using namespace cv;


class RVidStream
{
    private:
    bool m_flagConnected = false;
    bool m_flagConnecting = false;

    bool m_flagStream = false;

    bool m_debug;

    VideoWriter * m_writer;

    void stream_t(VideoCapture &source);

    string getPipeline(string IPaddr, int port);

    public:
    RVidStream(bool debug = true);

    bool target(string IPaddr, int port);

    bool stream(VideoCapture &source);
    void stopStream();
    
    void sendFrame(Mat &frame);
};