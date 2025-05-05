#include "../headers/RArUcoReader.hpp"

vector<RArUcoTag> RArUcoReader::getTags(Mat &im)
{
    vector<int> ids;
    vector<vector<Point2f> > corners;
    
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    aruco::detectMarkers(im, dictionary, corners, ids);

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
    }

    return tags;
}

RArUcoReader::RArUcoReader(Mat &image)
{
    m_frame = &image;
}

RArUcoReader::RArUcoReader(VideoCapture &vid)
{
    m_vid = &vid;
}

vector<RArUcoTag> RArUcoReader::grabFromFrame()
{
    if(m_frame != nullptr)
    {
        return getTags(*m_frame);
    }
    else
    {
        if(m_vid->isOpened())
        {
            Mat frame;
            *m_vid >> frame;

            if(!frame.empty())
            {
                return getTags(frame);
            }
        }
    }

    return {};
}

void RArUcoReader::extract(vector<RArUcoTag> tags, vector<int> &ids, vector<vector<Point2f>> &corners)
{
    vector<int> _ids;
    vector<vector<Point2f>> _corners;

    for(RArUcoTag tag : tags)
    {
        _ids.push_back(tag.getID());
        _corners.push_back(tag.getCorners());
    }

    ids = _ids;
    corners = _corners;
}

void RArUcoReader::drawTags(Mat &im, vector<RArUcoTag> tags)
{
    if(tags.size() > 0)
    {
        vector<int> ids;
        vector<vector<Point2f>> corners;

        extract(tags, ids, corners);
        aruco::drawDetectedMarkers(im, corners, ids);
    }
}

void RArUcoReader::drawArrows(Mat &im, vector<RArUcoTag> tags)
{
    for(RArUcoTag tag : tags)
    {
        tag.drawOrientationArrow(im);
    }
}