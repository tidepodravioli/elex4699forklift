#include <iostream>

#include "../../../../CLIENT/headers/RPiCamera.hpp"
#include "../../../../headers/RVidStream.hpp"

#define IP_ADDR_SERVER "192.168.0.110"
#define PORT_SERVER 5808

class RCameraServer
{
    private:

    public:
    RCameraServer();

    void start();
};