#include "../headers/RCameraCalibration.hpp"

RCameraCalibration::RCameraCalibration()
{

}

void RCameraCalibration::calibrate()
{
    // ---- SETTINGS ----
    

    // ---- CREATE BOARD ----
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dictionaryId);
    cv::Ptr<cv::aruco::GridBoard> board = cv::aruco::GridBoard::create(
        squaresX, squaresY, squareLength, markerLength, dictionary);

    // ---- OPEN CAMERA ----
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera." << std::endl;
        return -1;
    }

    std::vector<std::vector<cv::Point2f>> allCorners;
    std::vector<int> allIds;
    std::vector<cv::Mat> allImgs;

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
            allIds.insert(allIds.end(), ids.begin(), ids.end());
            allImgs.push_back(image.clone());
            collectedFrames++;
            std::cout << "Captured frame " << collectedFrames << "/" << requiredFrames << std::endl;
        }
    }

    // ---- CALIBRATE CAMERA ----
    std::cout << "Calibrating..." << std::endl;

    cv::Mat cameraMatrix, distCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;

    double rms = cv::aruco::calibrateCameraAruco(
        allCorners, allIds, board, cv::Size(allImgs[0].cols, allImgs[0].rows),
        cameraMatrix, distCoeffs, rvecs, tvecs);

    std::cout << "Calibration RMS error: " << rms << std::endl;
    std::cout << "Camera Matrix:\n" << cameraMatrix << std::endl;
    std::cout << "Distortion Coefficients:\n" << distCoeffs << std::endl;

    // ---- SAVE TO FILE ----
    cv::FileStorage fs("calibration.yaml", cv::FileStorage::WRITE);
    fs << "camera_matrix" << cameraMatrix;
    fs << "dist_coeffs" << distCoeffs;
    fs.release();

    std::cout << "Saved calibration to calibration.yaml\n";

    return 0;
}