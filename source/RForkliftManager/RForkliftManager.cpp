#include "../headers/RForkliftManager.hpp"

using namespace std;
using namespace cv;

RForkliftManager::RForkliftManager()
{
    gpioInitialise();
    registerCommands();
}

void RForkliftManager::start()
{
    setNonBlocking(true);
    setRawMode(true);

    m_flagRun = init();

    if(m_flagRun)
    {
        cout << "Starting server..." << endl;
    
        m_server.startServer(SERVER_PORT);
        m_flagRun = true;

        cout << "Server started! Listening on port " << SERVER_PORT << endl;
        while(m_flagRun)
        {
            getCom();
            update();
        }
    }

    cout << "Closing server..." << endl;
    m_server.stop();
    setNonBlocking(false);
    setRawMode(false);
}

bool RForkliftManager::init()
{
    cout << "RFORKLIFTMANAGER" << endl << "(C) R. BANALAN & R. CHAN 2025" << endl <<
    "BUILT ON " << BUILD_DATE << " " << BUILD_TIME << endl << endl;
    
    cout << "Checking GPIO privileges..." << endl;
    if(geteuid() != 0)
    {
        cout << "This program needs to be run as sudo!" << endl;
        return false;
    }
    cout << "Running as sudo, initializing GPIO..." << endl;

    cout << "Initializing motor driver...";
    m_driver = new RMotorDriverF(MOTOR_L1, MOTOR_L2, MOTOR_R1, MOTOR_R2, MOTOR_ENCL1, MOTOR_ENCL2, MOTOR_ENCR1, MOTOR_ENCR2);
    cout << " done." << endl;

    cout << "Initializing forklift servo...";
    m_forklift = new RPiForklift(FORKLIFT_SERVO);
    cout << " done." << endl;

    cout << "Manual mode services initialized! Checking automatic services..." << endl;
    cout << "Checking front camera...";
    
    m_camera = VideoCapture(0, CAP_V4L2);
    if(!m_camera.isOpened())
    {
        cout << " ERROR!" << endl;
        m_flagAutoAvailable = false;
    }
    else cout << " found." << endl;

    cout << "Init complete!" << endl;
    return true;
}

void RForkliftManager::getCom()
{
    vector<RControlEvent> newCommands;
    if(m_server.getCom(newCommands))
    {
        m_commandQueue.insert(m_commandQueue.end(), newCommands.begin(), newCommands.end());
    }
    
    // catch q button press for quit
    char ch;
    ssize_t n = read(STDIN_FILENO, &ch, 1);
    if (n > 0) {
        if (ch == 'q' | ch == 'Q') m_flagRun = false;
    }
}

void RForkliftManager::update()
{
    if(!m_commandQueue.empty())
    {
        RControlEvent current = m_commandQueue[0];

        cout << current.asCommand() << endl;

        handleCommand(current);

        m_commandQueue.erase(m_commandQueue.begin());
    }
}



