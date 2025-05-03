#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class RArUcoTag
{
    private:
    int m_tagID;
    vector<Point2f> m_corners;

    public:
    RArUcoTag(int tagID, vector<Point2f> corners);

    int getID();

    vector<Point2f> getCorners();

    Point2f getCenter();

    float getAngle();

    void drawOrientationArrow(Mat &image);

    static void extract(RArUcoTag tag, int &id, vector<Point2f> &corners);

    static void drawOrientationArrow(RArUcoTag tag,  Mat &image);
};