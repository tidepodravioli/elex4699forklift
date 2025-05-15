#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;

/**
 * @brief Represents an ArUco Tag with its data and position
 * @details RArUcoTag provides a means to calculate and determine
 * positional and rotational of a tag in 2D space. It is not meant
 * to be instantiated outside of a reader, as the parameters
 * needed to create one are inherent of the tag's actual position
 * in the real world.
 * 
 * It also provides some static functions that use existing RArUcoTags
 * to perform operations.
 */
class RArUcoTag
{
    private:
    int m_tagID;
    vector<cv::Point2f> m_corners;

    public:
    /**
     * @brief Creates a representation of an ArUco tag with the given tag ID and corner points.
     * (These are parameters returned by OpenCV's aruco detection library)
     * 
     * @param tagID The ID associated with the tag
     * @param corners The locations of each corner of the tag relative to its original Mat
     */
    RArUcoTag(int tagID, vector<cv::Point2f> corners);

    /**
     * @brief Gets the ID of this tag
     * 
     * @return int The tag ID
     */
    int getID();

    /**
     * @brief Gets the locations of the corners of the tag
     * 
     * @return vector<cv::Point2f> The corners of the tag, as a vector of Point2f's (sub-pixel coordinates)
     */
    vector<cv::Point2f> getCorners();

    /**
     * @brief Calculates the center of the tag using the locations of the corners
     * 
     * @return cv::Point2f The location of the center of the tag
     */
    cv::Point2f getCenter();

    /**
     * @brief Calculates the orientation of the tag as an angle.
     * This angle is flipped relative to regular cartesian coordinates.
     * For example, straight up on the image is -PI radians, straight down is +PI radians
     * 
     * @return float The orientation of the tag in radians
     */
    float getAngle_r();

    /**
     * @brief Calculates the orientation of the tag as an angle.
     * This angle is flipped relative to regular cartesian coordinates.
     * For example, straight up on the image is -90deg, straight down is +90deg
     * 
     * @return float The orientation of the tag in degrees
     */
    float getAngle_d();

    /**
     * @brief Draws an orientation arrow at the location of this tag on the given image
     * 
     * @param image The image to draw the arrow on
     */
    void drawOrientationArrow(cv::Mat &image);

    /**
     * @brief Returns the tag ID and corner locations of the given tag
     * 
     * @param tag The tag to get the ID and corners from
     * @param id Where to return the tag ID
     * @param corners Where to return the corner points
     */
    static void extract(RArUcoTag tag, int &id, vector<cv::Point2f> &corners);

    /**
     * @brief Draws an orientation arrow at the location of the given tag
     * 
     * @param tag The tag to draw on the image
     * @param image The image to draw the tag on
     */
    static void drawOrientationArrow(RArUcoTag tag,  cv::Mat &image);
};