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
            JOYSTICK_DIRECTION direction = jcurrent.getObj().get_simple_direction();

            switch(direction)
            {
                case JOYSTICK_DIRECTION_NORTH:
                    m_driver->forward();
                break;

                case JOYSTICK_DIRECTION_EAST:
                    m_driver->right();
                break;

                case JOYSTICK_DIRECTION_SOUTH:
                    m_driver->backward();
                break;

                case JOYSTICK_DIRECTION_WEST:
                    m_driver->left();
                break;
            }
        }
        else if(type == TYPE_DIGITAL)
        {
            if(origin == 1)
            {
                cout << "FORK UP" << endl;
                m_driver->write(40);
            }
            else if (origin == 2)
            {
                cout << "FORK DOWN" << endl;
                m_driver->write(60);
            }
        }

        m_commandQueue.erase(m_commandQueue.begin());
    }
    else
    {
        cout << "STOP" << endl;
        m_driver->stop();
    }
}

void RForkliftManager::react()
{
    
}