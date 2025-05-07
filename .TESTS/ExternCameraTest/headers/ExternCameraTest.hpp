#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

#include "../../../headers/RExternCamera.hpp"
#include "../../../shared/headers/ext/Client.h"
#include "../../../headers/RArUcoReader.hpp"

class ExternCameraTest
{
private:
    std::mutex * frame_m;
    bool flagExit = false;
    cv::Mat frame;
    void frame_t();
public:
    ExternCameraTest();

    void start();
    void startalt();
};
