#include <opencv2/opencv.hpp>

#include "../../client/headers/RAutoFork.hpp"

class AutoForkTest
{
    private:
    RPiCamera m_camera;
    RCoordinateHelper m_helper;
    RAutoFork m_fork;

    public:
    AutoForkTest();

    void start();
};