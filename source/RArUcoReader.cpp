#include "../headers/RArUcoReader.hpp"

static vector<RArUcoTag> RArUcoReader getTags(Mat &im)
{
    aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    aruco::ArucoDetector detector(dictionary, detectorParams);

    vector<int> ids;
    vector<vector<Point2f> > corners;
    detector.detectMarkers(frame, corners, ids);

    vector<RArUcoTag> tags;
    if (ids.size() > 0)
    {
        for(int index = 0; index < ids.size(); index++)
        {
            const int id = ids[index];
            vector<Point2f> _corners = corners[index];

            RArUcoTag tag(id, _corners);
            tags.push_back(tag);
        }
        RArUcoTag tag(id)
        aruco::drawDetectedMarkers(im, corners, ids);
    }
}