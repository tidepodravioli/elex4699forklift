#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

#include "RArUcoTag.hpp"
#include "RPiCamera.hpp"

using namespace std;
using namespace cv;

class RArUcoReader
{
    private:
    VideoCapture * m_vid = nullptr;
    Mat * m_frame = nullptr;

    vector<RArUcoTag> m_tags;

    public:
    RArUcoReader(Mat &image);
    RArUcoReader(VideoCapture &vid);

    vector<RArUcoTag> grabFromFrame();

    static vector<RArUcoTag> getTags(Mat &im);

    static void extract(vector<RArUcoTag> tags, vector<int> &ids, vector<vector<Point2f>> &corners);
    
    static void drawTags(Mat &im, vector<RArUcoTag> tags);

    static void drawArrows(Mat &im, vector<RArUcoTag> tags);
};