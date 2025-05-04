#include <iostream>

#include "../../../../headers/RPiCamera.hpp"
#include "../../../../headers/RVidStream.hpp"

#define IP_ADDR_SERVER "74.49.148.251"
#define PORT_SERVER 14606

class RCameraServer
{
    private:

    public:
    RCameraServer();

    void start();
};