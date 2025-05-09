#include <opencv2/opencv.hpp>

#define SQUARES_X 5
#define SQUARES_Y 7
#define SQUARE_LENGTH 0.04f  // in meters
#define MARKER_LENGTH 0.02f  // in meters
#define DICTIONARY_ID  cv::aruco::DICT_6x6_250
#define REQUIRED_FRAMES 15

class RCameraCalibration
{
    private:

    public:
    RCameraCalibration();

    void calibrate();
};