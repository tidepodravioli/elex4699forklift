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
            getCom();
            update();
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
    
    m_camera = VideoCapture(0, CAP_V4L2);
    if(!m_camera.isOpened())
    {
        cout << "Error opening front camera! Auto mode will be unavailable." << endl;
        m_flagAutoAvailable = false;
        return true;
    }
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

        const EVENT_COMMAND_TYPE com = current.getCom();
        const EVENT_DATA_TYPE type = current.getType();
        const int origin = current.getOrigin();

        if(com == ECOMMAND_SET)
        {

        }
        else if(com == ECOMMAND_GET)
        {
            if(type == ETYPE_COMMAND)
            {
                if(origin == 0)
                {
                    RControlEvent 
                }
            }
        }
        if(type == ETYPE_DIGITAL)
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
        else if(type == ETYPE_ANALOG)
        {
            cout << "JOYSTICK EVENT" << endl;
            RJoystickEvent jcurrent(current);
            m_driver->joystickDrive(jcurrent.percentX(), jcurrent.percentY());
        }
        else if(type == ETYPE_COMMAND)
        {
            if (origin == 0)
            {

            }
            else if (origin == 1)
            {

            }
            else if (origin == 2)
            {
                vector<string> data = current.getValues();
                
                const string IPaddr = data[0];
                const int port = stoi(data[1]);

                m_stream = new RVidStream();
                m_stream->target(IPaddr, port);
                m_stream->stream(m_camera);
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