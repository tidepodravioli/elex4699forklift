#include "../headers/RPiCamera.hpp"

using namespace std;

RPiCamera::RPiCamera(int index, int apiPreference) : VideoCapture(index, apiPreference)
{

}

bool RPiCamera::importCalibration(string filename)
{
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    if (!fs.isOpened()) {
        std::cerr << "Failed to open calibration file." << std::endl;
        return false;
    }

    fs["camera_matrix"] >> m_cameraMatrix;
    fs["dist_coeffs"] >> m_distCoeffs;
    fs.release();

    return true;
}

std::vector<RArUcoTag3> RPiCamera::getClosestTags(bool &valid)
{
    cv::Mat frame;
    read(frame);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;

    // Step 1: Detect markers in the frame
    m_reader._getTags(frame, corners, ids);

    if (ids.empty()) {
        valid = false;
        return {};
    }

    // Step 2: Estimate pose
    std::vector<cv::Vec3d> rvecs, tvecs;
    cv::aruco::estimatePoseSingleMarkers(corners, ARUCO_TAG_SIZE, m_cameraMatrix, m_distCoeffs, rvecs, tvecs);

    std::vector<RArUcoTag3> tags;

    for (int i = 0; i < tvecs.size(); ++i) {
        double distance = cv::norm(tvecs[i]);
        RArUcoTag3 tag(ids[i], corners[i], tvecs[i], rvecs[i]);

        bool inserted = false;
        for (auto it = tags.begin(); it != tags.end(); ++it) {
            if (distance <= it->getDistanceFromCamera()) {
                tags.insert(it, tag);
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            tags.push_back(tag); // Append at end if no closer one found
        }
    }

    valid = true;
    return tags;
}


bool RPiCamera::getDistanceClosestTag(float &distance)
{
    bool valid = false;
    vector<RArUcoTag3> tags = getClosestTags(valid);

    if(tags.size() > 0)
    {
        distance = tags[0].getDistanceFromCamera();
    }

    return valid;
}

bool RPiCamera::getTranslationClosestTag(cv::Vec3d &trans)
{
    bool valid = false;
    vector<RArUcoTag3> tags = getClosestTags(valid);

    if(tags.size() > 0)
    {
        trans = tags[0].getTrans();
    }

    return valid;
}