#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <iostream>

#include "../../../CLIENT/headers/RArUcoReader.hpp"
#include "../../../CLIENT/headers/RArUcoTag.hpp"


using namespace std;
using namespace cv;

class ArUcoTest
{
    private:

    public:
    ArUcoTest();

    void start();
};