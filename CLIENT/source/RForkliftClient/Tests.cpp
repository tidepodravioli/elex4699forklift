#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;


void RForkliftClient::cli_IOTest()
{  
    cli_getCControl();

    if(m_flagSerialConnected) while(!_kbhit())
    {
        bool joypass = false;
        CJoystickPosition analog = m_serial.get_analog(joypass);
        if(joypass)
        {
            if(analog.get_simple_direction() != JOYSTICK_DIRECTION_CENTER)
                cout << "JOYSTICK x= " << analog.getX() << ", y= " << analog.getY() << endl;
        }

        
        bool button1 = m_serial.get_button(0);
        bool button2 = m_serial.get_button(1);
        bool buttonj1 = m_serial.get_button(5);

        if(button1) cout << "BUTTON1 PRESSED" << endl;
        if(button2) cout << "BUTTON2 PRESSED" << endl;
        if(buttonj1) cout << "BUTTONJ1 PRESSED" << endl;
    }   
    
    cout << "Keypress detected. Returning to menu..." << endl;
    m_serial.~CControl();
    m_serial = CControl();

   
}

void RForkliftClient::gui_UITest()
{
    m_ui = new RDraw();
    while(!_kbhit())
    {
        //draw UI
        m_ui->drawArena();
        m_ui->drawUI();
    }

    cout << "Keypress detected. Returning to menu..." << endl;
    m_ui->~RDraw();
}

void RForkliftClient::cli_streamTest()
{
    cli_getSocket();
    if(m_flagConnected)
    {
        start_front_cam();

        do
        {
            cv::Mat frame;
            m_camstream >> frame;

            m_camstream.importCalibration(CAMERA_CALIBRATION);
            Vec3d trans;
            m_camstream.getTranslationClosestTag(trans);
            putText(frame, format("ANGLE: %0.5f", atan2(trans[0], trans[2])), Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1);
            putText(frame, format("DIST: %0.5f", norm(trans)), Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1);

            if(!frame.empty()) cv::imshow("TEST", frame);
        } 
        while (cv::waitKey(1) != 'q');
        
    }
}

void RForkliftClient::cli_antirafTest()
{
    cli_getSocket();

    if(m_flagConnected)
    {
        while(true)
        {
            int spx = 255, spy = 255;
            string command;
            prompt("Enter speeds : ", command, regex("^(|-)\\d+ (|-)\\d+$"), "Enter speeds delimited by space : ");
            
            vector<string> parts = delimitString(command, ' ');
            RControlEvent speedtest(ECOMMAND_SET, ETYPE_ANALOG, 1, parts);
            m_network.sendEvent(speedtest);
        }
    }
}

void RForkliftClient::cli_directCommandTest()
{
    cli_getSocket();

    if(m_flagConnected)
    {
        cout << "THIS TEST SENDS RAW UNFILTERED TEXT OVER THE NETWORK TO THE SERVER!!!" << endl
        << "PROCEED WITH CAUTION!!!" << endl;
        cout << setw(50) << setfill('-') << "-" << endl;

        while(true)
        {
            string command;
            get_line(&command);

            if(command == "q" || command == "Q") break;
            else m_network.tx_str(command);
        }

        m_network.disconnect();
    }
}

void RForkliftClient::cli_navToPickupTest()
{
    cli_getSocket();

    if(m_flagConnected)
    {
        start_front_cam();

        if(m_camstream.importCalibration(CAMERA_CALIBRATION))
        {
            cout << "Initializing motor writer..." << endl;
            m_writer = new RMotorWriter(m_network);

            while(true)
            {
                if(prompt_yn("Start test?"))
                {
                    Vec3d tagtranslation;
                    if(m_camstream.getTranslationClosestTag(tagtranslation))
                    {
                        Point2f dest(tagtranslation[0], tagtranslation[2]);
                        float angleErr = atan2(dest.x, dest.y);
                        cout << "ANGLE ERR : " << angleErr << endl;
                        m_writer->turn_r(angleErr);
                    }                    
                }
            }
        }
        else
        {
            cout << "Calibration failed. Exiting test..." << endl;
            return;
        }

        m_network.tx_str("S 2 1 0");
    }
}
