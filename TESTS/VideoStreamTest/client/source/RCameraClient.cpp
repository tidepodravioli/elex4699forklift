#include "../headers/RCameraClient.hpp"

RCameraClient::RCameraClient()
{

}

void RCameraClient::start()
{
    RVidReceiver receiver;
    receiver.listen(5808);

    
}