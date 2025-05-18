#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;

void RForkliftClient::start_front_cam()
{
    RControlEvent camerareq(ECOMMAND_SET, ETYPE_COMMAND, 2, 5808);
    m_network.sendEvent(camerareq);

    m_camstream.release();
    m_camstream.open(RVidReceiver::getPipeline(5808), CAP_GSTREAMER);

    this_thread::sleep_for(chrono::seconds(5));
}

void RForkliftClient::start_ui(Mat &init_arena)
{
    
}

void RForkliftClient::stop_ui()
{
    if(m_ui != nullptr)
    m_ui->~RDraw();
}