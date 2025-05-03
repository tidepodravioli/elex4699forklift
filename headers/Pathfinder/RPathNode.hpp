#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

class RPathNode
{
    private:
    int m_g, m_h;
    Point2i m_coords;
    RPathNode * m_nextNode;
    bool m_isObstacle;

    public:
    RPathNode(int x, int y, bool obstacle = false);
    RPathNode(Point2i coords, bool obstacle = false);
    RPathNode(Point2i coords, int g, int h, bool obstacle = false);
    
    
    void setCoords(int x, int y);
    void setCoords(Point2i coords);

    Point2i getCoords();

    void obstacle();
    void notobstacle();
    bool isObstacle();

    bool getNext(RPathNode &nextNode);

    void setNext(RPathNode * nextNode);

    void setg(int g);
    int getg();

    void seth(int h);
    int geth();
    
    int getf();

    bool operator ==(RPathNode &node);
};