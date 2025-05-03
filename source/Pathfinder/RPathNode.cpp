#include "../../headers/Pathfinder/RPathNode.hpp"

RPathNode::RPathNode(int x, int y, bool obstacle = false)
{
    setCoords(x,y);
    m_isObstacle = obstacle;
}

RPathNode::RPathNode(Point2i coords, bool obstacle = false)
{
    setCoords(coords);
    m_isObstacle = obstacle;
}

RPathNode::RPathNode(Point2i coords, int g, int h, bool obstacle = false)
{
    setCoords(coords);
    setg(g);
    seth(h);
    m_isObstacle = obstacle;
}

void RPathNode::setCoords(int x, int y)
{
    m_coords = Point2i(x,y);
}

void RPathNode::setCoords(Point2i coords)
{
    m_coords = coords;
}

Point2i RPathNode::getCoords()
{
    return m_coords;
}

void RPathNode::obstacle()
{
    m_isObstacle = true;
}

void RPathNode::notobstacle()
{
    m_isObstacle = false;
}

bool RPathNode::isObstacle()
{
    return m_isObstacle;
}

bool RPathNode::getNext(RPathNode &nextNode)
{
    if(m_nextNode != nullptr)
        {
            nextNode = *m_nextNode;
            return true;
        }
        else return false;
}

void RPathNode::setNext(RPathNode * nextNode)
{
    m_nextNode = nextNode; 
}

void RPathNode::setg(int g)
{
    m_g = g;
}

int RPathNode::getg()
{
    return m_g;
}

void RPathNode::seth(int h)
{
    m_h = h;
}

int RPathNode::geth()
{
    return m_h;
}

int RPathNode::getf()
{
    return m_g + m_h;
}

bool RPathNode::operator==(RPathNode &node)
{
    return (m_coords.x == node.m_coords.x) && (m_coords.y == node.m_coords.y); 
}