#include "../headers/AutoForkTest.hpp"

AutoForkTest::AutoForkTest() : m_camera(0, cv::CAP_DSHOW), m_helper(1, true), m_fork(m_camera, m_helper)
{
    m_camera.importCalibration("./calibration.yaml");
}

void AutoForkTest::start()
{
    cv::Mat frame;

    while(true)
    {
        m_camera >> frame;
        m_fork.dock();
        cv::imshow("AutoForkTest", frame);
        cv::waitKey(1);
    }
}
