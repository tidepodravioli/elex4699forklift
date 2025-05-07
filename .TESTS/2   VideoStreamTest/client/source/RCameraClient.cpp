#include "../headers/RCameraClient.hpp"

RCameraClient::RCameraClient()
{

}

void RCameraClient::start()
{
    RVidReceiver receiver;
    receiver.listen(5808);

    cout << "Starting..." << endl;

    Mat frame;
    do
    {
        if(receiver.getFrame(frame))
        {
            imshow("RECEIVER TEST", frame);
        }
    }
    while(waitKey(1) != 'q');

    cout << "Exiting..." << endl;
}