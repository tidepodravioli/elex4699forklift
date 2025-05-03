#include <vector>
#include <opencv2/opencv.hpp>

#include "RPathNode.hpp"

using namespace std;
using namespace cv;

class RPathMap
{
    private:
    vector<RPathNode> m_nodes;
    Size2i m_imageSize;

    public:
    /**
     * @brief Creates an RPathMap given an image and the dimensions of the square dividing the board
     * 
     * @param im Image to divide into square cells
     * @param div Number to divide image by
     */
    RPathMap(Mat &im, int div);

    vector<RPathNode> getNeighbours();
};