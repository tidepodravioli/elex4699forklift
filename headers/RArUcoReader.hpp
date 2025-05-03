#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

#include "RArUcoTag.hpp"

using namespace std;
using namespace cv;

class RArUcoReader
{
    private:

    public:
    RArUcoReader();

    static vector<RArUcoTag> getTags(Mat &im); 
};