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
            m_camstream.read(frame);
            if(!frame.empty()) cv::imshow("TEST", frame);
        } 
        while (cv::waitKey(20) != 'q');
        
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
