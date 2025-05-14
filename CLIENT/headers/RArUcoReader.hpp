#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

#include "RArUcoTag.hpp"

using namespace std;
using namespace cv;

#ifdef NEW_OPENCV_CONF
#pragma message("NEW_OPENCV will be used for RArUcoReader")
#else
#pragma message("NEW_OPENCV will NOT be used for RArUcoReader")
#endif

/**
 * @brief Provides an interface to continuously get ArUco tags from a video stream.
 * @details RArUcoReader is an interface that can either read the tags from a frame
 * or a continuous stream. It does this by instantiating a dictionary and detector
 * inside of itself to speed up the detection process. When using the reader explicitly,
 * grabFromFrame() will get the tags from the Mat given in its constructor or the next
 * available frame from the VideoCapture object.
 * 
 * When used implicitly, a reader may be instantiated to provide quick reading of tags. The
 * function getTags() can then be used by passing a Mat to it and obtaining the resulting
 * vector of RArUCo tags.
 * 
 * There are also static functions available for use in RArUcoReader, namely extract(),
 * drawTags(), and drawArrows(), all of which work on existing vectors of tags
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
    /**
     * @brief Constructs a new RArUcoReader for implicit use. Only instantiates the reader and dictionary
     * 
     */
    RArUcoReader();

    /**
     * @brief Constructs a new RArUcoReader that reads from one image explicitly
     * 
     * @param image The image to read from
     */
    RArUcoReader(Mat &image);

    /**
     * @brief Constructs a new RArUcoReader that reads from a video stream
     * 
     * @param vid Video stream to read from
     */
    RArUcoReader(VideoCapture &vid);

    /**
     * @brief Reads tags from the Mat given in the constructor, or the next frame of the given VideoCapture
     * 
     * @return vector<RArUcoTag> The tags in the frame
     */
    vector<RArUcoTag> grabFromFrame();

    /**
     * @brief Reads tags from the given Mat frame
     * 
     * @param im The image to read the tags from
     * @return vector<RArUcoTag> The tags read from the frame
     */
    vector<RArUcoTag> getTags(Mat &im);

    void getTags(Mat &im, vector<vector<Point2f>> &corners, vector<int> &ids);

    /**
     * @brief Extracts the data from a collection of tags
     * 
     * @param tags The tags to extract from
     * @param ids The ids of each tag
     * @param corners The locations of the corners of each tag
     */
    static void extract(vector<RArUcoTag> tags, vector<int> &ids, vector<vector<Point2f>> &corners);
    
    /**
     * @brief Draws the given tags on an image
     * 
     * @param im The image to draw the tags on
     * @param tags The tags to draw on the image
     */
    static void drawTags(Mat &im, vector<RArUcoTag> tags);

    /**
     * @brief Draws arrows showing which way a collection of tags is pointing
     * 
     * @param im The image to draw the arrows on
     * @param tags The tags to draw the arrows for
     */
    static void drawArrows(Mat &im, vector<RArUcoTag> tags);
};