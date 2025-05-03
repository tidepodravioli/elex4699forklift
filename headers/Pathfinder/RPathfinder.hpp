#include <opencv2/opencv.hpp>
#include <vector>

#include "RPathNode.hpp"

using namespace std;
using namespace cv;

class RPathfinder
{
    private:

    public:
    RPathfinder(Mat &im, int divisor);

    void defineObstacle(Point2i cell);

    void defineObstacles(vector<Point2i> obstacles);

    vector<RPathNode> findPath(RPathNode startNode, RPathNode targetNode);
};