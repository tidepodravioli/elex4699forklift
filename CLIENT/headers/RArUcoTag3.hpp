#pragma once 

#include <opencv2/opencv.hpp>
#include <vector>
#include "RArUcoTag.hpp"


/**
 * @brief Represents an ArUco tag in 3D space. (Child of RArUcoTag)
 * @details RArUcoTag3, like RArUcoTag, represents an ArUco tag, but in 3D space instead.
 * It is also not meant to be instantiated outside of readers and other functions that
 * create them.
 */
class RArUcoTag3 : public RArUcoTag
{
    private:
    cv::Vec3d m_rot, m_trans;

    public:
    /**
     * @brief Construct a new RArUcoTag3 object
     * 
     * @param tagID The ID associated with the tag
     * @param corners The locations of each corner of the tag relative to its original Mat
     * @param rot The rotational vectors representing its rotation in 3D space
     * @param trans It's translational vectors relative to the center of its original Mat
     */
    RArUcoTag3(int tagID, std::vector<cv::Point2f> corners, cv::Vec3d rot, cv::Vec3d trans);

    /**
     * @brief Gets the 3D rotational vector of the tag
     * 
     * @return Vec3d The rotational vector
     */
    cv::Vec3d getRot();

    /**
     * @brief Get the 3D translational vector of the tag, relative to the center of its original Mat
     * 
     * @return Vec3d The translational vector
     */
    cv::Vec3d getTrans();

    /**
     * @brief Gets the distance from the camera to the tag, as the normalized length of the translational vector
     * 
     * @return float The distance from the camera
     */
    float getDistanceFromCamera();
};