#include "../headers/RExternCamera.hpp"

RExternCamera::RExternCamera()
{

}

void RExternCamera::connect(string IPaddr, int port, int channel)
{
    m_camera.connect_socket(IPaddr, port);
    m_channel = channel;
}

void RExternCamera::disconnect()
{
    m_camera.close_socket();
}

void RExternCamera::ping()
{
    stringstream command;
    command << "G " << m_channel << " \n";

    m_camera.tx_str(command.str());
}

void RExternCamera::getFrame(Mat &im)
{
    m_camera.rx_im(im);
}