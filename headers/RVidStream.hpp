#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>

#include "RPiCamera.hpp"

#define ARUCO_TAG_CAMERA 24
#define ARUCO_TAG_PKG1 5
#define ARUCO_TAG_PKG2 6
#define ARUCO_TAG_TRK1 1
#define ARUCO_TAG_TRK2 2
#define ARUCO_TAG_TRK3 3
#define ARUCO_TAG_TRK4 4

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