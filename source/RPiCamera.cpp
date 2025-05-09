#include "../headers/RPiCamera.hpp"

RPiCamera::RPiCamera(int index, int apiPreference) : VideoCapture(index, apiPreference)
{
    m_dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
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

vector<RArUcoTag3> RPiCamera::getClosestTags(bool &valid)
{
    Mat frame;
    read(frame);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;

    // Step 1: Detect markers in the frame
    cv::aruco::detectMarkers(frame, m_dictionary, corners, ids);

    // If no markers detected, return a large number (indicating no markers in the frame)
    if (ids.empty()) {
        valid = false;
        return {};
    }

    // Step 2: Estimate pose for each detected marker
    std::vector<cv::Vec3d> rvecs, tvecs;
    cv::aruco::estimatePoseSingleMarkers(corners, ARUCO_TAG_SIZE, m_cameraMatrix, m_distCoeffs, rvecs, tvecs); // Assuming marker length of 0.1 meters (adjust if needed)

    vector<RArUcoTag3> tags;

    for (int i = 0; i < tvecs.size(); ++i) {
        // Compute the Euclidean distance to the marker from the camera
        double distance = cv::norm(tvecs[i]);  // Euclidean distance from the camera to the marker
        
        for(int j = 0; j < tags.size(); j++)
        {
            RArUcoTag3 tag(ids[i], corners[i], tvecs[i], rvecs[i]);
            if(distance <= tags[j].getDistanceFromCamera())
            {
                tags.insert(tags.begin() + j, tag);
                break;
            }
            else
            {
                tags.push_back(tag);
                break;
            }
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

bool RPiCamera::getTranslationClosestTag(Vec3d &trans)
{
    bool valid = false;
    vector<RArUcoTag3> tags = getClosestTags(valid);

    if(tags.size() > 0)
    {
        trans = tags[0].getTrans();
    }

    return valid;
}