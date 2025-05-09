#include "../headers/RArUcoTag3.hpp"

RArUcoTag3::RArUcoTag3(int tagID, std::vector<Point2f> corners, Vec3d rot, Vec3d trans) : RArUcoTag(tagID, corners)
{
    m_rot = rot;
    m_trans = trans;
}

Vec3d RArUcoTag3::getRot()
{
    return m_rot;
}

Vec3d RArUcoTag3::getTrans()
{
    return m_trans;
}
