#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <iostream>

#include "../../../headers/RArUcoReader.hpp"
#include "../../../headers/RArUcoTag.hpp"
#include "../../../headers/RPiCamera.hpp"


using namespace std;
using namespace cv;

class ArUcoTest
{
    private:

    public:
    ArUcoTest();

    void start();
};