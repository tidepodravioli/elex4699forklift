#include "../headers/RAutoFork.hpp"

RAutoFork::RAutoFork()
{

}

bool RAutoFork::importCalibration(string fileName)
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

float RAutoFork::getDistanceClosestTag(Mat &im)
{
    
}