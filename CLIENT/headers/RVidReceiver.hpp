#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace std;
using namespace cv;

class RVidReceiver
{
    private:
    bool m_flagConnected = false;

    bool m_debug;

    VideoCapture * m_camera;

    string getPipeline(int port);

    public:
    RVidReceiver(bool debug = true);

    void listen(int port);

    bool getFrame(Mat &im);
};