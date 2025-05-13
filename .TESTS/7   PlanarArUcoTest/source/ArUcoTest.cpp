#include "../headers/ArUcoTest.hpp"

ArUcoTest::ArUcoTest()
{
    
}

void ArUcoTest::start()
{
    RCoordinateHelper helper(1, true);
    helper.connect_socket("192.168.1.101", 5008);
    helper.startFrameGetter();

    RPiCamera camera;
    bool calib = camera.importCalibration("../calibration.yaml");
    if(calib) cout << "Calibration successful!" << endl;

    while(true)
    {
        const Point2i coords = helper.getRobotCoords();
        const float angle = helper.getRobotAngle_r();

        Vec3d trans;
        camera.getTranslationClosestTag(trans);

        const float prop_angle = M_PI - angle;

        const double x0 = coords.x + trans[2] * cos(prop_angle) + trans[0] * sin(prop_angle);
        const double y0 = coords.y + trans[2] * sin(prop_angle) - trans[0] * cos(prop_angle);

        Mat image;
        helper.getFrame(image);
        circle(image, Point2d(x0, y0), 20, Scalar(0,0,255));

        imshow("TEST", image);
        waitKey(1);
    }
}

bool ArUcoTest::importCalibration(string fileName)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    if (!fs.isOpened()) {
        std::cerr << "Failed to open calibration file." << std::endl;
        return false;
    }

    fs["camera_matrix"] >> m_cameraMatrix;
    fs["dist_coeffs"] >> m_distCoeffs;
    fs.release();

    return true;
}

double ArUcoTest::getDistanceToClosestMarker(cv::Mat& frame, cv::Ptr<cv::aruco::Dictionary> dictionary) {
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;

    // Step 1: Detect markers in the frame
    cv::aruco::detectMarkers(frame, dictionary, corners, ids);

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