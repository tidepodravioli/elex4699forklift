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

    cout << "Front camera found!" << endl;
    return true;
}

void RForkliftManager::getCom()
{
    vector<RControlEvent> newCommands;
    if(m_server.getCom(newCommands))
    {
        m_commandQueue.insert(m_commandQueue.end(), newCommands.begin(), newCommands.end());
    }
    
    char ch;
    ssize_t n = read(STDIN_FILENO, &ch, 1);
    if (n > 0) {
        if (ch == 'q') m_flagRun = false;
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

        cout << current.asCommand() << endl;

        handleCommand(current);

        m_commandQueue.erase(m_commandQueue.begin());
    }
    else
    {
        
    }
}

void RForkliftManager::automode()
{
    
}

void RForkliftManager::setNonBlocking(bool enable) {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (enable)
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    else
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void RForkliftManager::setRawMode(bool enable) {
    static termios oldt;
    static bool saved = false;

    if (enable) {
        termios newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);  // raw mode
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        saved = true;
    } else if (saved) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // restore
    }
}

