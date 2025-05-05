#include <opencv2/opencv.hpp>
#include <string>

#include "../shared/headers/ext/Client.h"

#define OVERHEAD_CAMERA_CHANNEL 1

using namespace std;
using namespace cv;

class RExternCamera
{
private:
    bool m_flagConnected = false;

    CClient m_camera;

public:
    RExternCamera();

    bool connect(string IPaddr, int port, int channel = OVERHEAD_CAMERA_CHANNEL);

    void disconnect();

    void getFrame(Mat &im);
};