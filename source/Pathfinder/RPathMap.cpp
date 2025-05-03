#include "../../headers/Pathfinder/RPathMap.hpp"

RPathMap::RPathMap(Mat &im, int div)
{
    m_imageSize = im.size();
    int numcellsx = m_imageSize.width / div;
    int numcellsy = m_imageSize.height / div;

    for(int ix = 0; ix < numcellsx; ix++)
    {
        for(int iy = 0; iy < numcellsy; iy++)
        {
            RPathNode cell(ix, iy);
        }
    }
}

vector<RPathNode> getNeighbours(RPathNode &node)
{
    
}