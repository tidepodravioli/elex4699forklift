#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>

#define SQUARES_X 5
#define SQUARES_Y 4
#define MARKER_DIST 0.005f  // in meters
#define MARKER_LENGTH 0.0395f  // in meters
#define DICTIONARY_ID  cv::aruco::DICT_6X6_250
#define REQUIRED_FRAMES 15
#define CALIB_IDS {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}

class RCameraCalibration
{
    private:

    public:
    RCameraCalibration();

    bool calibrate();
};