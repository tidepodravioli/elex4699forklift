#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace std;

class RVidReceiver : public cv::VideoCapture
{
    private:
    bool m_flagConnected = false;

    bool m_debug;

    string getPipeline(int port);

    public:
    RVidReceiver(bool debug = true);

    void listen(int port);

    bool getFrame(cv::Mat &im);
};