#include "../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;

void RForkliftClient::start()
{
    while(true)
    {
        cli_showMenu();

        char option;
        get_char(&option);

        switch(option)
        {
            case '1':
                cli_startClient();
            break;

            case '2':
                cli_IOTest();
            break;

            case '3':
                cli_streamTest();
            break;

            case '4':
                gui_UITest();
            break;

            case 's':
                cli_settings();
            break;

            case 'q':
                return;
            break;

            default:
                cout << "Please enter a valid option..." << endl;
            break;
        }
    }
}

void RForkliftClient::cli_showMenu()
{
    cout << endl << endl;
    cout << setw(50) << setfill('=')  << "=" << endl;
    cout << setfill(' ') << setw(32) << right << "RForkliftClient" << endl;
    cout << setw(50) << setfill('=') << "=" << endl << endl;

    cout << "(C) R.BANALAN & R.CHAN 2025" << endl;
    cout << setw(50) << setfill('-') << "-";
    cout << endl << endl;

    cout << "Select an option:" << endl
    << "(1) Connect to forklift server" << endl 
    << "(2) Serial IO test" << endl
    << "(3) PI Video Stream test" << endl
    << "(4) UI test" << endl << endl
    << "(s) Settings" << endl
    << "(q) Quit" << endl
    << "> ";
}

void RForkliftClient::cli_settings()
{
    while(true)
    {
        cout << endl << endl << "DEBUG SETTINGS MENU" << endl;
        cout << "Select an option to toggle it T/F" << endl << endl;

        cout << "(1) Require CControl serial to connect to server [" << (m_flagManualAvailable ? "TRUE]" : "FALSE]") << endl
        << "(2) Require connection to front camera [" << (m_flagFrontCamNeeded ? "TRUE]" : "FALSE]")<< endl
        << "(3) Require connection to overhead camera [" << (m_flagArenaCamNeeded ? "TRUE]" : "FALSE]")<< endl
        << "> ";

        char option;
        get_char(&option);
        switch(option)
        {
            case '1':
            m_flagManualAvailable = !m_flagManualAvailable;
            break;

            case '2':
            m_flagFrontCamNeeded = !m_flagFrontCamNeeded;
            break;

            case '3':
            m_flagArenaCamNeeded = !m_flagArenaCamNeeded;
            break;

            case 'q':
            return;
        }
    }
}

void RForkliftClient::cli_getSocket()
{
    cout << endl << "CONNECTION TO FORKLIFT SERVER" << endl;
    
    string IPaddr;
    prompt("Enter server IP address : ", IPaddr, regex(E4618_IPADDR_REGEX), "Please enter formatted IPv4 address : ");

    cout << "Enter target port : ";
    int port;
    bool valid = false;
    while(!valid)
    {
        valid = get_int(&port);
        valid &= port >= 0 && port <= 65535;

        if(valid) break;
        cout << "Please enter valid port : ";
    }

    cout << "Connecting..." << endl;
    m_flagConnected = m_network.connect(IPaddr, port);
    
}

void RForkliftClient::cli_getCControl()
{
    cout << endl << endl << "CONNECTION TO SERIAL CONTROLLER" << endl;

   int serialport;
   prompt("Enter serial port number : ", serialport, "Please enter a valid number : ");

   cout << "Connecting..." << endl;
   m_serial.init_com(serialport);

   cout << "Checking connection..." << endl;
   if(m_serial.checkPort())
   {
        m_flagSerialConnected = true;
        cout << "Connected to COM" << serialport << "!" << endl;
   }
   else
   {
        m_flagSerialConnected = false;
        cout << "Invalid response from serial port." << endl;
        return;
   }
}

void RForkliftClient::cli_startClient()
{   
    cli_getSocket();
    if(m_flagConnected && m_flagManualAvailable) cli_getCControl();

    if(m_flagConnected && (m_flagSerialConnected || !m_flagManualAvailable))
    {
        cout << "Initializing services..." << endl;

        cout << "Initializing motor writer..." << endl;
        m_writer = new RMotorWriter(m_network);

        if(m_flagFrontCamNeeded)
        {
            cout << "Establishing front camera stream..." << endl;
            start_front_cam();

            Mat testframe;
            m_camstream.read(testframe);
            if(!testframe.empty() && m_camstream.isOpened())
            {
                cout << "Front camera stream established!" << endl;
                cout << "Loading calibration..." << endl;
                if(m_camstream.importCalibration("../../calibration.yaml"))
                    cout << "Calibration successful!" << endl;
                    else cout << "Could not read calibration file...";
                m_flagFrontCamConnected = true;
            }
            else
            {
                cout << "Connection failed or no image received from stream..." << endl;
                m_flagFrontCamConnected = false;
            } 

        }
        else cout << "Front camera will NOT be initialized" << endl;

        if(m_flagArenaCamNeeded)
        {
            cout << "Connecting to overhead camera..." << endl;
            m_helper = RCoordinateHelper();
            m_helper.connect_socket(ARENA_CAMERA_IP, ARENA_CAMERA_PORT);
            this_thread::sleep_for(chrono::milliseconds(500));
            m_helper.refreshRobot();
            Mat testframe;
            m_helper.getFrame(testframe);

            if(!testframe.empty())
            {
                imshow("TESTFRAME", testframe);
                waitKey(1);
            }
            if(m_helper.robotFound())
            {
                cout << "Robot was found on the playfield at " << m_helper.getRobotCoords() << endl
                << "Overhead camera connection successful!" << endl;
                
                m_flagArenaCamConnected = true;
            }
            else
            {
                cout << "Robot was not found on the playfield. Prior to initialization, ensure that the robot can be seen by the overhead camera!" << endl;
                m_flagArenaCamConnected = false;
            }
        }
        else cout << "Arena camera will NOT be initialized" << endl;

        cout << "Establishing auto pilot..." << endl;
        m_autopilot = new RAutoPilot(*m_writer, m_helper);
        

        if(!m_flagManualAvailable) cout << "Manual mode will be unavailable. If manual mode is needed, please enable it in the settings." << endl;
        cout << "Press any key on the keyboard to break the connection and return to the menu" << endl;
        cout << setw(50) << setfill('-') << "-" << endl;

        proc_client();
    }    
}

void RForkliftClient::proc_client()
{
    while(!_kbhit())
    {
        //draw UI
        m_ui.drawArena();
        //m_ui.drawUI();

        m_flagAutoMode = m_ui.getAuto();
        m_flagSlowMode = !m_ui.getFast();
        m_flagRun = m_ui.getStart();

        // Runs the processing for auto/manual mode
        if(m_flagAutoMode) proc_auto();
        else if(m_flagManualAvailable) proc_manual();
    }   
    cout << "Keypress detected. Disconnecting from server." << endl;
    m_network.disconnect();
    m_camstream.release();
    m_helper.close_socket();

    m_flagArenaCamConnected = false;
    m_flagFrontCamConnected = false;
    m_flagSerialConnected = false;
    m_flagConnected = false;
}

void RForkliftClient::proc_manual()
{
    bool joypass = false;
    CJoystickPosition analog = m_serial.get_analog(joypass);
    if(joypass)
    {
        if(analog.get_simple_direction() != JOYSTICK_DIRECTION_CENTER)
            cout << "JOYSTICK x= " << analog.getX() << ", y= " << analog.getY() << endl;
        RJoystickEvent joystickEvent(analog);
            m_network.sendEvent(joystickEvent);
    }


    bool button1 = m_serial.get_button(0);
    bool button2 = m_serial.get_button(1);
    bool buttonj1 = m_serial.get_button(5);

    if(button1)
    { 
        cout << "BUTTON1 PRESSED" << endl;
        RControlEvent buttonEvent(ECOMMAND_SET, ETYPE_DIGITAL, 1, 1);
        m_network.sendEvent(buttonEvent);
    }

    if(button2) 
    {
        cout << "BUTTON2 PRESSED" << endl;
        RControlEvent buttonEvent(ECOMMAND_SET, ETYPE_DIGITAL, 2, 1);
        m_network.sendEvent(buttonEvent);
    }

    if(buttonj1)
    {
        cout << "BUTTONJ1 PRESSED" << endl;
        RControlEvent buttonEvent(ECOMMAND_SET, ETYPE_DIGITAL, 5, 1);
        m_network.sendEvent(buttonEvent);
    }
}

void RForkliftClient::proc_auto()
{
    // 1. Navigate to pickup point

    // 2. Pick-up package

    // 3. Drive to drop-off point

    // 4. Drop off package

    //For now though, we're testing the driving lol

    vector<Point2i> path;
    while(!m_flagRun && m_flagAutoMode)
    {
        path = m_ui.getPathAsPoints();
    }

    if(m_flagRun && m_flagAutoMode)
    {
        m_autopilot->drivePath(path);
        m_ui.setStart(false);
    }
}

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
    while(!_kbhit())
    {
        //draw UI
        m_ui.drawArena();
        m_ui.drawUI();
    }

    cout << "Keypress detected. Returning to menu..." << endl;
    m_ui.~RDraw();
    m_ui = RDraw();
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

void RForkliftClient::start_front_cam()
{
    RControlEvent camerareq(ECOMMAND_SET, ETYPE_COMMAND, 2, 5808);
    m_network.sendEvent(camerareq);

    m_camstream.release();
    m_camstream.open(RVidReceiver::getPipeline(5808), CAP_GSTREAMER);

    this_thread::sleep_for(chrono::seconds(5));
}

void RForkliftClient::t_showFrontCam()
{

}