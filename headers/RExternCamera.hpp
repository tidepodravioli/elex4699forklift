#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

#include <iostream>

#include "../shared/headers/ext/Client.h"

#define OVERHEAD_CAMERA_CHANNEL 1

using namespace std;
using namespace cv;

class RExternCamera
{
private:
    bool m_flagConnected = false;

    int m_channel = OVERHEAD_CAMERA_CHANNEL;

    CClient m_camera;

public:
    RExternCamera();

    void connect(string IPaddr, int port, int channel = OVERHEAD_CAMERA_CHANNEL);

    void disconnect();

    void ping();

    void getFrame(Mat &im);
};