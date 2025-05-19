#include "../headers/RForkliftManager.hpp"

using namespace std;
using namespace cv;

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