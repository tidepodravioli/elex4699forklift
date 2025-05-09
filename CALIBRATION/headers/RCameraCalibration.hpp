#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

#define SQUARES_X 7
#define SQUARES_Y 5
#define SQUARE_LENGTH 0.045f  // in meters
#define MARKER_LENGTH 0.040f  // in meters
#define DICTIONARY_ID  cv::aruco::DICT_6X6_250
#define REQUIRED_FRAMES 15

class RCameraCalibration
{
    private:

    public:
    RCameraCalibration();

    bool calibrate();
};