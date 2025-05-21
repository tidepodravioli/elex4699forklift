#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;

void RForkliftClient::cli_settings()
{
    while(true)
    {
        cout << endl << endl << "DEBUG SETTINGS MENU" << endl;
        cout << "Select an option to toggle it T/F" << endl << endl;

        cout << "(1) Require CControl serial to connect to server [" << (m_flagManualAvailable ? "TRUE]" : "FALSE]") << endl
        << "(2) Require connection to front camera [" << (m_flagFrontCamNeeded ? "TRUE]" : "FALSE]")<< endl
        << "(3) Require connection to overhead camera [" << (m_flagArenaCamNeeded ? "TRUE]" : "FALSE]")<< endl
        << "> ";

        char option;
        get_char(&option);
        switch(option)
        {
            case '1':
            m_flagManualAvailable = !m_flagManualAvailable;
            break;

            case '2':
            m_flagFrontCamNeeded = !m_flagFrontCamNeeded;
            break;

            case '3':
            m_flagArenaCamNeeded = !m_flagArenaCamNeeded;
            break;

            case 'q':
            return;
        }
    }
}

void RForkliftClient::cli_getSocket()
{
    cout << endl << "CONNECTION TO FORKLIFT SERVER" << endl;

    bool useLast = false;
    if(m_lastPort != -1) useLast = prompt_yn("Would you like to connect using the last connected socket settings?");

    string IPaddr;
    int port;

    if(useLast)
    {
        IPaddr = m_lastIP;
        port = m_lastPort;
    }
    else
    {
        prompt("Enter server IP address : ", IPaddr, regex(E4618_IPADDR_REGEX), "Please enter formatted IPv4 address : ");

        cout << "Enter target port : ";
        bool valid = false;
        while(!valid)
        {
            valid = get_int(&port);
            valid &= port >= 0 && port <= 65535;

            if(valid) break;
            cout << "Please enter valid port : ";
        }

        m_lastIP = IPaddr;
        m_lastPort = port;
    }
    
    

    cout << "Connecting..." << endl;
    m_flagConnected = m_network.connect(IPaddr, port);
    
}

void RForkliftClient::cli_getCControl()
{
    cout << endl << endl << "CONNECTION TO SERIAL CONTROLLER" << endl;

   int serialport;
   prompt("Enter serial port number : ", serialport, "Please enter a valid number : ");

   cout << "Connecting..." << endl;
   m_serial.init_com(serialport);

   cout << "Checking connection..." << endl;
   if(m_serial.checkPort())
   {
        m_flagSerialConnected = true;
        cout << "Connected to COM" << serialport << "!" << endl;
   }
   else
   {
        m_flagSerialConnected = false;
        cout << "Invalid response from serial port." << endl;
        return;
   }
}
