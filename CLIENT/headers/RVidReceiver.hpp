#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>


class RVidReceiver : public cv::VideoCapture
{
    private:
    bool m_flagConnected = false;

    bool m_debug;

    std::string getPipeline(int port);

    public:
    RVidReceiver(bool debug = true);

    bool listen(int port);

    bool getFrame(cv::Mat &im);
};