#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>

#include "RPiCamera.hpp"

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

    void startServer_t(string IPaddr, int port);
    void stream_t(VideoCapture &source);

    public:
    RVidStream(bool debug = true);

    bool target(string IPaddr, int port);

    bool stream(VideoCapture &source);
    bool stream(RPiCamera &camera);
    void stopStream();
    
    void sendFrame(Mat &frame);
};