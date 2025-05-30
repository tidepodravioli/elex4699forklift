#include "../headers/RArUcoReader.hpp"

using namespace std;

vector<RArUcoTag> RArUcoReader::getTags(cv::Mat &im)
{
    vector<int> ids;
    vector<vector<cv::Point2f> > corners;

    #ifdef NEW_OPENCV_CONF
    m_detector->detectMarkers(im, corners, ids);
    #else
    cv::aruco::detectMarkers(im, m_dictionary, corners, ids);
    #endif

    vector<RArUcoTag> tags;
    if (ids.size() > 0)
    {
        for(int index = 0; index < ids.size(); index++)
        {
            const int id = ids[index];
            vector<cv::Point2f> _corners = corners[index];

            RArUcoTag tag(id, _corners);
            tags.push_back(tag);
        }
    }

    return tags;
}

void RArUcoReader::_getTags(cv::Mat &im, vector<vector<cv::Point2f>> &corners, vector<int> &ids)
{
    #ifdef NEW_OPENCV_CONF
    m_detector->detectMarkers(im, corners, ids);
    #else
    cv::aruco::detectMarkers(im, m_dictionary, corners, ids);
    #endif
}

RArUcoReader::RArUcoReader()
{
    config();
}

RArUcoReader::RArUcoReader(cv::Mat &image)
{
    m_frame = &image;
    config();
}

RArUcoReader::RArUcoReader(cv::VideoCapture &vid)
{
    m_vid = &vid;
    config();
}

void RArUcoReader::config()
{
    #ifdef NEW_OPENCV_CONF
        m_detectorParams = cv::aruco::DetectorParameters();
        m_dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
        m_detector = new cv::aruco::ArucoDetector(m_dictionary, m_detectorParams);
    #else
        m_dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    #endif
}

vector<RArUcoTag> RArUcoReader::grabFromFrame()
{
    if(m_frame != nullptr)
    {
        return getTags(*m_frame);
    }
    else if(m_vid != nullptr)
    {
        if(m_vid->isOpened())
        {
           cv::Mat frame;
            *m_vid >> frame;

            if(!frame.empty())
            {
                return getTags(frame);
            }
        }
    }
    else return {};
}

void RArUcoReader::extract(vector<RArUcoTag> tags, vector<int> &ids, vector<vector<cv::Point2f>> &corners)
{
    vector<int> _ids;
    vector<vector<cv::Point2f>> _corners;

    for(RArUcoTag tag : tags)
    {
        _ids.push_back(tag.getID());
        _corners.push_back(tag.getCorners());
    }

    ids = _ids;
    corners = _corners;
}

void RArUcoReader::drawTags(cv::Mat &im, vector<RArUcoTag> tags)
{
    if(tags.size() > 0)
    {
        vector<int> ids;
        vector<vector<cv::Point2f>> corners;

        extract(tags, ids, corners);
        cv::aruco::drawDetectedMarkers(im, corners, ids);
    }
}

void RArUcoReader::drawArrows(cv::Mat &im, vector<RArUcoTag> tags)
{
    for(RArUcoTag tag : tags)
    {
        tag.drawOrientationArrow(im);
    }
}