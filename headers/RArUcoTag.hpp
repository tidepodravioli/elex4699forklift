#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class RArUcoTag
{
    private:
    int m_tagID;
    vector<Point2i> corners;

    public:
    RArUcoTag(int tagID, vector<Point2i> corners);

    int getID();

    Point2i getCenter();
}