#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;


void RForkliftClient::t_showFrontCam()
{
    while(m_flagFrontCamConnected)
    {
        Mat frame;
        m_camstream >> frame;

        if(!frame.empty())
        {
            putText(frame, format("FORK POSITION: %d", m_writer->forkIndex()), Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            imshow("Onboard camera", frame);
            waitKey(1);
        }
    }
}

void RForkliftClient::t_showArenaCam()
{
    do
    {
        Mat frame;
        m_helper.refreshRobot();
        if(m_helper.getFrame(frame))
        {
            imshow("Arena camera (q to exit)", frame);
        }
    }
    while(m_flagArenaCamShow && waitKey(1) != 'q');

    m_flagArenaCamShow = false;
}

void RForkliftClient::t_refreshUI()
{
    
}
