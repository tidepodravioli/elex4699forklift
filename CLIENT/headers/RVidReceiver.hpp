#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace std;

class RVidReceiver
{
    private:
    bool m_flagConnected = false;

    bool m_debug;

    cv::VideoCapture * m_camera;

    string getPipeline(int port);

    public:
    RVidReceiver(bool debug = true);

    void listen(int port);

    bool getFrame(cv::Mat &im);
};