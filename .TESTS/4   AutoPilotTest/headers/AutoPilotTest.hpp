#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "../../headers/RAutoPilot.hpp"
#include "../../headers/RMotorDriver.hpp"
#include "../../CLIENT/headers/ext/getstuff.h"

#define MOTOR_L1 4
#define MOTOR_L2 17
#define MOTOR_R1 27
#define MOTOR_R2 22

#define IP_ADDR "192.168.0.101"
#define PORT 5008

using namespace std;
using namespace cv;

class AutoPilotTest
{
    public:
    AutoPilotTest();

    void start();

    vector<string> delimitString(std::string input, char delimiter);
};