#include "../headers/RForkliftClient.hpp"

void RForkliftClient::start()
{
    cout << "RForkliftClient" << endl
        << "(C) R.BANALAN & R.CHAN 2025" << endl << endl;

    cout << "Press (1) to connect to the server" << endl 
        << "or (2) for IO test." << endl << endl
        << "(q) at any time quits the program." << endl;

    while(true)
    {
        char option;
        get_char(&option);

        switch(option)
        {
            case '1':
                gui_getSocket();
                gui_startClient();
            break;

            case '2':
                gui_IOTest();
            break;

            case 'q':
                return;
            break;

            default:
                cout << "Please enter a valid option..." << endl;
            break;
        }
    }
}

void RForkliftClient::gui_getSocket()
{
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

    cout << "Connecting..." << endl;
    m_network.connect(IPaddr, port);
    
}

void RForkliftClient::gui_startClient()
{
    cout << "Enter serial port number : ";

   int serialport;
   while(!get_int(&serialport))
   {
        cout << "Please enter a number : ";
   }

   cout << "Connecting..." << endl;
   m_serial.init_com(serialport);

   cout << "Checking connection..." << endl;
   if(m_serial.checkPort())
   {
    cout << "Connected!" << endl;

    while(!_kbhit())
    {
        bool joypass = false;
        CJoystickPosition analog = m_serial.get_analog(joypass);
        if(joypass)
        {
            if(analog.get_simple_direction() != JOYSTICK_DIRECTION_CENTER)
            {
                RJoystickEvent joystickEvent(analog);
                m_network.sendEvent(joystickEvent);
            }
        }

        
        bool button1 = m_serial.get_button(0);
        bool button2 = m_serial.get_button(1);

        if(button1)
        { 
            cout << "Button 1 pressed" << endl;
            RControlEvent buttonEvent(TYPE_DIGITAL, 1, 1);
            m_network.sendEvent(buttonEvent);
        }

        if(button2) 
        {
            cout << "Button 2 pressed" << endl;
            RControlEvent buttonEvent(TYPE_DIGITAL, 2, 1);
            m_network.sendEvent(buttonEvent);
        }
    }   
    cout << "Keypress detected. Exiting program...";
    }
   else
   {
    cout << "Invalid response from serial port." << endl;
    return;
   }
    
}
void RForkliftClient::gui_IOTest()
{  
   cout << "Enter serial port number : ";

   int serialport;
   while(!get_int(&serialport))
   {
        cout << "Please enter a number : ";
   }

   cout << "Connecting..." << endl;
   m_serial.init_com(serialport);

   cout << "Checking connection..." << endl;
   if(m_serial.checkPort())
   {
    cout << "Connected!" << endl;

    while(!_kbhit())
    {
        bool joypass = false;
        CJoystickPosition analog = m_serial.get_analog(joypass);
        if(joypass)
        {
            if(analog.get_simple_direction() != JOYSTICK_DIRECTION_CENTER)
            {
                cout << setw(10) << analog.percentX() << setw(10) << analog.percentY() << endl;
            }
        }

        
        bool button1 = m_serial.get_button(0);
        bool button2 = m_serial.get_button(1);

        if(button1) cout << "BUTTON 1 pressed." << endl;
        if(button2) cout << "BUTTON 2 pressed." << endl;
    }   
    
    cout << "Keypress detected. Exiting program...";

   }
   else
   {
    cout << "Invalid response from serial port." << endl;
    return;
   }
}