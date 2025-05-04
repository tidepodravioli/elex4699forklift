#include "../headers/RCameraServer.hpp"

RCameraServer::RCameraServer()
{

}

void RCameraServer::start()
{
    RPiCamera camera;
    RVidStream streamer;

    streamer.target(IP_ADDR_SERVER, PORT_SERVER);
    streamer.stream(camera);

    std::cout << "Stream started" << endl;
    while(true);
}