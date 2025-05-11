#include "../headers/RArUcoTag.hpp"

RArUcoTag::RArUcoTag(int tagID, vector<Point2f> corners)
{
    m_tagID = tagID;
    m_corners = corners;
}

int RArUcoTag::getID()
{
    return m_tagID;
}

vector<Point2f> RArUcoTag::getCorners()
{
    return m_corners;
}

Point2f RArUcoTag::getCenter()
{
    cv::Point2f center(0, 0);
    for (const auto& pt : m_corners) {
        center += pt;
    }
    center *= (1.0f / static_cast<float>(m_corners.size()));
    return center;
}

float RArUcoTag::getAngle_r()
{
    if (m_corners.size() < 2) return 0.0f;

    cv::Point2f vec = m_corners[0] - m_corners[1];  // vector from corner 0 to 1
    float angleRad = std::atan2(vec.y, vec.x);  // radians
    
    return angleRad;
}

float RArUcoTag::getAngle_d()
{
    float angleRad = getAngle_r();
    float angleDeg = angleRad * 180.0f / CV_PI;

    return angleDeg;
}

void RArUcoTag::drawOrientationArrow(Mat &image)
{
    cv::Point2f center = getCenter();

    // Arrow length in pixels (adjust as needed)
    float length = 40.0f;

    // Convert angle to radians for trig
    float angleRad = getAngle_r();

    // Compute end point of arrow
    cv::Point2f end = center + cv::Point2f(
        std::cos(angleRad) * length,
        std::sin(angleRad) * length
    );

    cv::arrowedLine(image, center, end, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
}

void RArUcoTag::extract(RArUcoTag tag, int &id, vector<Point2f> &corners)
{
    id = tag.getID();
    corners = tag.getCorners();
}

void RArUcoTag::drawOrientationArrow(RArUcoTag tag, Mat& image) {
    cv::Point2f center = tag.getCenter();

    // Arrow length in pixels (adjust as needed)
    float length = 40.0f;

    // Convert angle to radians for trig
    float angleRad = tag.getAngle_d() * CV_PI / 180.0f;

    // Compute end point of arrow
    cv::Point2f end = center + cv::Point2f(
        std::cos(angleRad) * length,
        std::sin(angleRad) * length
    );

    cv::arrowedLine(image, center, end, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
}
