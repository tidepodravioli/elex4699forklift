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

bool RPiCamera::getClosestTag(RArUcoTag3D &tag)
{
    Mat frame;
    read(frame);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;

    // Step 1: Detect markers in the frame
    cv::aruco::detectMarkers(frame, m_dictionary, corners, ids);

    // If no markers detected, return a large number (indicating no markers in the frame)
    if (ids.empty()) {
        return -1;
    }

    // Step 2: Estimate pose for each detected marker
    std::vector<cv::Vec3d> rvecs, tvecs;
    cv::aruco::estimatePoseSingleMarkers(corners, 0.065f, m_cameraMatrix, m_distCoeffs, rvecs, tvecs); // Assuming marker length of 0.1 meters (adjust if needed)

    // Step 3: Calculate the distance to each marker
    double minDistance = std::numeric_limits<double>::max();  // Initialize with a large number

    for (size_t i = 0; i < tvecs.size(); ++i) {
        // Compute the Euclidean distance to the marker from the camera
        double distance = cv::norm(tvecs[i]);  // Euclidean distance from the camera to the marker
        if (distance < minDistance) {
            minDistance = distance;  // Update if this marker is closer
        }
    }

    return minDistance;  // Return the distance to the closest marker
}

bool RPiCamera::getDistanceClosestTag(float &distance)
{
    Mat frame;
    read(frame);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;

    // Step 1: Detect markers in the frame
    cv::aruco::detectMarkers(frame, m_dictionary, corners, ids);

    // If no markers detected, return a large number (indicating no markers in the frame)
    if (ids.empty()) {
        return -1;
    }

    // Step 2: Estimate pose for each detected marker
    std::vector<cv::Vec3d> rvecs, tvecs;
    cv::aruco::estimatePoseSingleMarkers(corners, 0.065f, m_cameraMatrix, m_distCoeffs, rvecs, tvecs); // Assuming marker length of 0.1 meters (adjust if needed)

    // Step 3: Calculate the distance to each marker
    double minDistance = std::numeric_limits<double>::max();  // Initialize with a large number

    for (size_t i = 0; i < tvecs.size(); ++i) {
        // Compute the Euclidean distance to the marker from the camera
        double distance = cv::norm(tvecs[i]);  // Euclidean distance from the camera to the marker
        if (distance < minDistance) {
            minDistance = distance;  // Update if this marker is closer
        }
    }

    return minDistance;  // Return the distance to the closest marker
}