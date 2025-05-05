#include "../headers/RCameraServer.hpp"

RCameraServer::RCameraServer()
{

}

void RCameraServer::start()
{
    VideoCapture camera(0, CAP_V4L2);
    RVidStream streamer(true);

    streamer.target(IP_ADDR_SERVER, PORT_SERVER);
    if(streamer.stream(camera))
    {
        std::cout << "Stream started" << endl;
        while(true);
    }

    std::cout << "Failed to open stream" << endl;
}