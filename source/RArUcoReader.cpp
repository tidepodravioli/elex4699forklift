#include "../headers/RArUcoReader.hpp"

vector<RArUcoTag> RArUcoReader::getTags(Mat &im)
{
    vector<int> ids;
    vector<vector<Point2i> > corners;
    
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    aruco::detectMarkers(im, dictionary, corners, ids);

    vector<RArUcoTag> tags;
    if (ids.size() > 0)
    {
        for(int index = 0; index < ids.size(); index++)
        {
            const int id = ids[index];
            vector<Point2i> _corners = corners[index];

            RArUcoTag tag(id, _corners);
            tags.push_back(tag);

            RArUcoTag tag(id, _corners);
            tags.push_back(tag);
        }
    }

    return tags;
}