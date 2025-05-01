#include <iostream>
#include <regex>
#include <string>
#include "ext/getstuff.h"

#define E4618_IPADDR_REGEX "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$"


using namespace std;
using namespace raf_cin;

class RForkliftClient
{
    private:
    void gui_getSocket();

    public:
    RForkliftClient() {}

    void start();

    
};