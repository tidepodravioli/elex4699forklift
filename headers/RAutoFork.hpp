#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <chrono>

#include "RPiCamera.hpp"
#include "RAutoPilot.hpp"
#include "RCoordinateHelper.hpp"
#include "RArUcoTag3.hpp"
#include "RPiForklift.hpp"
#include "ForkliftConstants.h"

using namespace cv;
using namespace std;

class RAutoFork
{
    private:
    RPiCamera * m_camera;
    RAutoPilot * m_autopilot;
    RCoordinateHelper * m_helper;
    RPiForklift * m_forklift;
    RArUcoTag3 m_closest_tag;
    Point2i m_packageCoords;
    vector<Point2i> m_dropOffCoords = {Point2i(0, 0), Point2i(0, 0), Point2i(0, 0)};
    std::chrono::seconds m_backupTime = std::chrono::seconds(FORKLIFT_BACKUP_TIME);


    public:
    RAutoFork(&RPiCamera &camera, &RAutoPilot &autopilot, &RCoordinateHelper &helper, &RPiForklift &forklift);

    void approachPackage();

    void pickUpPackage();

    void driveToDropOff();

    void dropOffPackage();

    void reset();

    void run();
};