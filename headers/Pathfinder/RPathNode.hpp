#include <vector>

class RPathNode
{
    private:
    int m_g, m_h;
    std::pair<int,int> * m_coords;
    RPathNode * m_nextNode;
    bool m_isObstacle;

    public:
    RPathNode(int g, int h, bool obstacle = false)
    {
        m_g = g;
        m_h = h;
        m_isObstacle = obstacle;
    }
    
    void setCoords(int x, int y) { m_coords = new std::pair<int,int>(x,y); }
    void setCoords(std::pair<int,int> coords) { m_coords = &coords; }

    bool getCoords(std::pair<int,int> &coords)
    {
        if(m_coords != nullptr)
        {
            coords = *m_coords;
            return true;
        }
        else return false;
    }

    bool getNext(RPathNode &nextNode)
    {
        if(m_nextNode != nullptr)
        {
            nextNode = *m_nextNode;
            return true;
        }
        else return false;
    }

    void setNext(RPathNode * nextNode) { m_nextNode = nextNode; }

    int getf() { return m_g + m_h; }
};