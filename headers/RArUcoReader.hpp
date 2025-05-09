#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

#include "RArUcoTag.hpp"
#include "RPiCamera.hpp"

using namespace std;
using namespace cv;

#ifdef NEW_OPENCV_CONF
#pragma message("NEW_OPENCV will be used for RArUcoReader")
#else
#pragma message("NEW_OPENCV will NOT be used for RArUcoReader")
#endif

/**
 * @brief Provides an interface to continuously get ArUco tags from a video stream.
 * 
 */
class RArUcoReader
{
    private:
    VideoCapture * m_vid = nullptr;
    Mat * m_frame = nullptr;

    vector<RArUcoTag> m_tags;

    #ifdef NEW_OPENCV_CONF
    aruco::DetectorParameters m_detectorParams;
    aruco::Dictionary m_dictionary;
    aruco::ArucoDetector * m_detector;
    #else
    Ptr<aruco::Dictionary> m_dictionary;
    #endif

    void config();

    public:
    RArUcoReader();
    RArUcoReader(Mat &image);
    RArUcoReader(VideoCapture &vid);

    vector<RArUcoTag> grabFromFrame();

    //vector<RArUcoTag> getTags();
    vector<RArUcoTag> getTags(Mat &im);

    static void extract(vector<RArUcoTag> tags, vector<int> &ids, vector<vector<Point2f>> &corners);
    
    static void drawTags(Mat &im, vector<RArUcoTag> tags);

    static void drawArrows(Mat &im, vector<RArUcoTag> tags);
};