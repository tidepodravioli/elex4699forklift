#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;

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

            if(m_helper.robotFound())
            {
                cout << "Robot was found on the playfield at " << m_helper.getRobotCoords() << endl
                << "Overhead camera connection successful!" << endl;
                
                m_flagArenaCamConnected = true;
                Mat frame;
                m_helper.getFrame(frame);
                m_ui = new RDraw(frame);
            }
            else
            {
                cout << "Robot was not found on the playfield. Prior to initialization, ensure that the robot can be seen by the overhead camera!" << endl;
                m_flagArenaCamConnected = false;
            }
        }
        else
        {
            cout << "Arena camera will NOT be initialized" << endl;
            m_ui = new RDraw();
        }

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
        m_ui->drawArena();
        m_ui->drawUI();

        m_flagAutoMode = m_ui->getAuto();
        m_flagSlowMode = !m_ui->getFast();
        m_flagRun = m_ui->getStart();

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

    m_ui->~RDraw();
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

    if(m_flagRun && m_flagAutoMode)
    {
        m_flagThreadedUIrefresh = true;
        //thread ui_t(&RForkliftClient::t_refreshUI, this);
        //ui_t.detach();

        path = m_ui->getPathAsPoints();
        cout << "Driving given path... (" << path.size() << " node(s))" << endl;
        m_autopilot->drivePath(path);
        cout << "Destination reached!" << endl;
        m_ui->setStart(false);

        m_flagThreadedUIrefresh = false;
        //ui_t.join();
    }
}