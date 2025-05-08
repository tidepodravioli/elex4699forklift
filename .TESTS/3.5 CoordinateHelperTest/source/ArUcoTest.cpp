#include "../headers/ArUcoTest.hpp"

ArUcoTest::ArUcoTest()
{

}

void ArUcoTest::start()
{
    cout << "ArUcoTest starting." << endl;
    
    RPiCamera camera(0, CAP_DSHOW);
    RArUcoReader reader;

    if(camera.isOpened())
    {
        do
        {
            Mat frame;
            if(camera.read(frame))
            {   
                vector<RArUcoTag> tags = reader.getTags(frame);
                for(RArUcoTag tag : tags)
                {
                    if(tag.getID() == 188)
                    {
                        tag.drawOrientationArrow(frame);
                        cout << "COORDS : " << tag.getCenter() << " , ANGLE : " << tag.getAngle() << endl; 
                        break;
                    }
                }

                imshow("ArUcoTest", frame);
            }
            else cout << "Empty frame" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        while(waitKey(1) != 'q');
    }
    else cout << "Error init camera" << endl;
}