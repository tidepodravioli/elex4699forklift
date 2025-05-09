#pragma once 

#include <opencv2/opencv.hpp>
#include <vector>
#include "RArUcoTag.hpp"

using namespace cv;

class RArUcoTag3 : public RArUcoTag
{
    private:
    Vec3d m_rot, m_trans;

    public:
    RArUcoTag3(int tagID, std::vector<Point2f> corners, Vec3d rot, Vec3d trans);

    Vec3d getRot();

    Vec3d getTrans();

    float getDistanceFromCamera();
};