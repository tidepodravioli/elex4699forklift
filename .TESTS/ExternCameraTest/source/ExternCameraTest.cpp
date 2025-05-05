#include "../headers/ExternCameraTest.hpp"

void ExternCameraTest::start()
{
    RExternCamera camera;
    camera.connect("192.168.0.100", 4008);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    Mat frame;
    do
    {
        camera.getFrame(frame);

        if (!frame.empty())
        {
            cv::imshow("EXTERN CAMERA TEST", frame);
        }
    } while (cv::waitKey(1) != 'q');
}