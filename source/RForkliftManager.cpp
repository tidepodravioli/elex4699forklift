#include "../headers/RForkliftManager.hpp"

RForkliftManager::RForkliftManager()
{
    gpioInitialise();
}

void RForkliftManager::start()
{
    m_driver = new RMotorDriver(MOTOR_L1, MOTOR_L2, MOTOR_R1, MOTOR_R2);
    m_forklift = new RPiForklift(FORKLIFT_SERVO);

    cout << "Starting server..." << endl;
    
    m_server.startServer();
    m_flagRun = true;
    
    while(m_flagRun)
    {
        getCom();
        update();
        react();
    }
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
                m_driver->forward();

                cout << gpioGetMode(MOTOR_L1) << endl;
                cout << gpioGetMode(MOTOR_L2) << endl;
            }
            else if (origin == 2)
            {
                cout << "FORK DOWN" << endl;
                m_driver->backward();
            }
        }

        m_commandQueue.erase(m_commandQueue.begin());
    }
    else
    {
        m_driver->stop();
    }
}

void RForkliftManager::react()
{
    
}