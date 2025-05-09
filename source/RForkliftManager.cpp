#include "../headers/RForkliftManager.hpp"

RForkliftManager::RForkliftManager()
{
    gpioInitialise();
}

void RForkliftManager::start()
{
    m_flagRun = init();

    if(m_flagRun)
    {
        cout << "Starting server..." << endl;
    
        m_server.startServer();
        m_flagRun = true;

        cout << "Server started!" << endl;
        
        while(m_flagRun)
        {
            if(m_flagManual)
            {
                getCom();
                update();
            }
            else
            {
                automode();
            }
            
        }
    }

    cout << "Closing server..." << endl;
}

bool RForkliftManager::init()
{
    cout << "RFORKLIFTMANAGER" << endl << "(C) R. BANALAN & R. CHAN 2025" << endl << endl;
    
    cout << "Checking GPIO privileges..." << endl;
    if(geteuid() != 0)
    {
        cout << "This program needs to be run as sudo!" << endl;
        return false;
    }
    cout << "Running as sudo, initializing GPIO..." << endl;

    cout << "Initializing motor driver..." << endl;
    m_driver = new RMotorDriver(MOTOR_L1, MOTOR_L2, MOTOR_R1, MOTOR_R2);
    
    cout << "Initializing forklift servo..." << endl;
    m_forklift = new RPiForklift(FORKLIFT_SERVO);

    cout << "Manual mode services initialized! Checking automatic services..." << endl;
    cout << "Checking front camera..." << endl;
    if(!m_camera.isOpened())
    {
        cout << "Error opening front camera! Auto mode will be unavailable." << endl;
        m_flagAutoAvailable = false;
        return true;
    }

    cout << "Checking overhead camera..." << endl;
    m_helper = new RCoordinateHelper();
    m_helper->connect_socket(ARENA_CAMERA_IP, ARENA_CAMERA_PORT);
    this_thread::sleep_for(chrono::milliseconds(100));
    m_helper->startFrameGetter();
    m_helper->refreshRobot();
    if(!m_helper->robotFound())
    {
        cout << "Could not find robot on the arena! Auto mode will be unavailable." << endl;
        m_flagAutoAvailable = false;
        return true;
    }

    cout << "Auto mode services initialized! Init pass!" << endl;
    return true;
}

void RForkliftManager::getCom()
{
    vector<RControlEvent> newCommands;
    if(m_server.getCom(newCommands))
    {
        m_commandQueue.insert(m_commandQueue.end(), newCommands.begin(), newCommands.end());
    }
}

void RForkliftManager::update()
{
    if(!m_commandQueue.empty())
    {
        RControlEvent current = m_commandQueue[0];
        const DATA_TYPE type = current.getType();
        const int origin = current.getOrigin();

        if(type == TYPE_ANALOG)
        {
            cout << "JOYSTICK EVENT" << endl;
            RJoystickEvent jcurrent(current);
            m_driver->joystickDrive(jcurrent.percentX(), jcurrent.percentY());
        } 
        else if(type == TYPE_DIGITAL)
        {
            if(origin == 1)
            {
                cout << "FORK UP" << endl;
                m_forklift->write(45);
            }
            else if (origin == 2)
            {
                cout << "FORK DOWN" << endl;
                m_forklift->write(20);
            }
            else if(origin == 5)
            {
                cout << "SLOW MODE" << endl;
                m_driver->toggleSlow();
            }
        }

        m_commandQueue.erase(m_commandQueue.begin());
    }
    else
    {
        
    }
}

void RForkliftManager::automode()
{
    
}