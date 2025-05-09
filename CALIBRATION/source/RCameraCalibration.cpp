#include "../headers/RCameraCalibration.hpp"

RCameraCalibration::RCameraCalibration()
{

}

bool RCameraCalibration::calibrate()
{
    // ---- CREATE BOARD ----
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(DICTIONARY_ID);
    cv::Ptr<cv::aruco::GridBoard> board = cv::aruco::GridBoard::create(
        SQUARES_X, SQUARES_Y, MARKER_LENGTH, MARKER_DIST, dictionary);

    // ---- OPEN CAMERA ----
    cv::VideoCapture cap(0, cv::CAP_V4L2);
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera." << std::endl;
        return false;
    }

    std::vector<std::vector<cv::Point2f>> allCorners;
    std::vector<cv::Mat> allImgs;
    std::vector<int> numMarkers;

    int collectedFrames = 0;

    std::cout << "Press SPACE to capture frame with detected board. ESC to calibrate and quit.\n";

    while (true) {
        cv::Mat image;
        cap >> image;
        if (image.empty()) break;

        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        if (!ids.empty())
            cv::aruco::drawDetectedMarkers(image, corners, ids);

        cv::imshow("Calibration", image);
        char key = (char)cv::waitKey(10);

        if (key == 27 && collectedFrames >= 5) break;  // ESC
        else if (key == ' ' && !ids.empty()) {
            allCorners.insert(allCorners.end(), corners.begin(), corners.end());
            allImgs.push_back(image.clone());
            numMarkers.push_back(ids.size());

            collectedFrames++;
            std::cout << "Captured frame " << collectedFrames << "/" << REQUIRED_FRAMES << std::endl;
        }
    }

    if (collectedFrames < 5) {
        std::cerr << "Not enough frames collected. Exiting.\n";
        return -1;
    }

    // ---- CALIBRATE CAMERA ----
    std::cout << "Calibrating..." << std::endl;

    cv::Mat cameraMatrix, distCoeffs;
    cv::Mat rvecs, tvecs;

    const std::vector<int> allIds = CALIB_IDS;
    double rms = cv::aruco::calibrateCameraAruco(
        allCorners, allIds, numMarkers, board, cv::Size(allImgs[0].cols, allImgs[0].rows),
        cameraMatrix, distCoeffs, rvecs, tvecs);

    std::cout << "Calibration RMS error: " << rms << std::endl;
    std::cout << "Camera Matrix:\n" << cameraMatrix << std::endl;
    std::cout << "Distortion Coefficients:\n" << distCoeffs << std::endl;

    // ---- SAVE TO FILE ----
    cv::FileStorage fs("../calibration.yaml", cv::FileStorage::WRITE);
    fs << "camera_matrix" << cameraMatrix;
    fs << "dist_coeffs" << distCoeffs;
    fs.release();

    std::cout << "Saved calibration to calibration.yaml\n";

    return true;
}