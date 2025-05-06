#include "../headers/ExternCameraTest.hpp"

ExternCameraTest::ExternCameraTest()
{

}

void ExternCameraTest::start()
{
    RExternCamera camera;
    camera.connect("192.168.0.100", 5008, 1);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    Mat frame;
    do
    {
        camera.ping();
        camera.getFrame(frame);

        if (!frame.empty())
        {
            cv::imshow("EXTERN CAMERA TEST", frame);
        }
        
    } while (cv::waitKey(1) != 'q');
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
        Mat copy = frame.clone();
        frame_m->unlock();

        if(!copy.empty())
        {
            std::vector<RArUcoTag> tags = reader.getTags(copy);
            reader.drawTags(copy, tags);
            cv::imshow("TEST", copy);
        }
        
    }
    while(cv::waitKey(1) != 'q');
}

void ExternCameraTest::frame_t()
{
    CClient client;
    client.connect_socket("192.168.0.101", 4008);

    while(!flagExit)
    {
        client.tx_str("G 1");
        
        frame_m->lock();
        client.rx_im(frame);
        frame_m->unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}