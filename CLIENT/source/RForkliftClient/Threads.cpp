#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;


void RForkliftClient::t_showFrontCam()
{

}

void RForkliftClient::t_refreshUI()
{
    while(m_flagThreadedUIrefresh)
    {
        Mat frame;
        if(m_helper.getFrame(frame))
        {
            m_ui->drawArena(frame);
            m_ui->drawUI();
        }
    }
}
