#include "../headers/RArUcoTag3.hpp"

RArUcoTag3::RArUcoTag3(int tagID, std::vector<cv::Point2f> corners, cv::Vec3d rot, cv::Vec3d trans) : RArUcoTag(tagID, corners)
{
    m_rot = rot;
    m_trans = trans;
}

cv::Vec3d RArUcoTag3::getRot()
{
    return m_rot;
}

cv::Vec3d RArUcoTag3::getTrans()
{
    return m_trans;
}

float RArUcoTag3::getDistanceFromCamera()
{
    return cv::norm(m_trans);
}