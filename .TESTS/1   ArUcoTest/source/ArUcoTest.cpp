#include "../headers/ArUcoTest.hpp"

ArUcoTest::ArUcoTest()
{

}

void ArUcoTest::start()
{
    cout << "ArUcoTest starting." << endl;
    
    VideoCapture camera;
    camera.open(0, CAP_DSHOW);

    RArUcoReader reader;

    if(camera.isOpened())
    {
        do
        {
            Mat frame;
            if(camera.read(frame))
            {   
                vector<RArUcoTag> tags = reader.getTags(frame);
                RArUcoReader::drawTags(frame, tags);
                RArUcoReader::drawArrows(frame, tags);

                imshow("ArUcoTest", frame);
            }
            else cout << "Empty frame" << endl;
        }
        while(waitKey(20) != 'q');
    }
    else cout << "Error init camera" << endl;
}