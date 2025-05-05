#include "../headers/RExternCamera.hpp"

RExternCamera::connect(string IPaddr, int port, int channel)
{
    m_camera.connect_socket(IPaddr, port);
}

void RExternCamera::disconnect()
{
    m_camera.close_socket();
}

void RExternCamera::getFrame(Mat &im)
{
    m_camera.rx_im(im);
}