#include "../headers/ExternCameraTest.hpp"

using namespace std;
using namespace cv;

ExternCameraTest::ExternCameraTest()
{

}

void ExternCameraTest::start()
{
    
}

void ExternCameraTest::startalt()
{
    frame_m = new std::mutex();
    RArUcoReader reader;

    std::thread framegetter_t(&ExternCameraTest::frame_t, this);
    framegetter_t.detach();

    do
    {
        frame_m->lock();
        cv::Mat copy = frame.clone();
        frame_m->unlock();

        if(!copy.empty())
        {
            std::vector<RArUcoTag> tags = reader.getTags(copy);
            for(RArUcoTag tag : tags)
            {
                std::cout << "Heading : " << tag.getAngle_r() << endl;
            }
            reader.drawTags(copy, tags);
            cv::imshow("TEST", copy);
        }
        
    }
    while(cv::waitKey(1) != 'q');
}

void ExternCameraTest::frame_t()
{
    CClient client;
    client.connect_socket("192.168.0.100", 4008);

    while(!flagExit)
    {
        client.tx_str("G 1");
        
        frame_m->lock();
        client.rx_im(frame);
        frame_m->unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}