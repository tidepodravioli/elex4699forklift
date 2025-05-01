#include "../headers/RForkliftClient.hpp"

void RForkliftClient::start()
{

}

void RForkliftClient::gui_getSocket()
{
    cout << "RForkliftClient" << endl
        << "(C) R.BANALAN & R.CHAN 2025" << endl << endl;

    cout << "Enter server IP address : ";
    string IPaddr;
    while(!get_data(&IPaddr,regex(E4618_IPADDR_REGEX)))
    {
        cout << "Please enter IPv4 address : ";
    }

    cout << "Enter target port : ";
    int port;
    bool valid = false;
    while(!valid)
    {
        valid = get_int(&port);
        valid &= port >= 0 && port <= 65535;

        if(valid) break;
        cout << "Please enter valid port : ";
    }

    cout << "Connecting...";
    
}