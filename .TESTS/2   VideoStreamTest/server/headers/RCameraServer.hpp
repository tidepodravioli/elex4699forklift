#include <iostream>

#include "../../../../headers/RPiCamera.hpp"
#include "../../../../headers/RVidStream.hpp"

#define IP_ADDR_SERVER "10.0.0.65"
#define PORT_SERVER 5808

class RCameraServer
{
    private:

    public:
    RCameraServer();

    void start();
};