#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace std;

class RVidReceiver
{
    public:
    RVidReceiver();

    void listen(int port);
};