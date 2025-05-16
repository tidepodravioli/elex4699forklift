#include "../headers/RForkliftClient.hpp"

void RForkliftClient::start()
{
    while(true)
    {
        gui_showMenu();

        char option;
        get_char(&option);

        switch(option)
        {
            case '1':
                gui_getSocket();

                if(m_flagConnected)
                    gui_startClient();
            break;

            case '2':
                gui_IOTest();
            break;

            case '3':
                gui_UITest();
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

void RForkliftClient::gui_showMenu()
{
    cout << endl << endl;
    cout << setw(50) << setfill('=')  << "=" << endl;
    cout << setfill(' ') << setw(32) << right << "RForkliftClient" << endl;
    cout << setw(50) << setfill('=') << "=" << endl << endl;

    cout << "(C) R.BANALAN & R.CHAN 2025" << endl;
    cout << setw(50) << setfill('-') << "-";
    cout << endl << endl;

    cout << "Select an option:" << endl
    << "(1) Connect to forklift server" << endl 
    << "(2) Serial IO test." << endl
    << "(3) UI test." << endl << endl
    << "(q) Quit" << endl
    << "> ";
}

void RForkliftClient::gui_getSocket()
{
    cout << endl << "CONNECTION TO FORKLIFT SERVER" << endl;
    cout << "Enter server IP address : ";
    string IPaddr;
    while(!get_data(&IPaddr,regex(E4618_IPADDR_REGEX)))
    {
        cout << "Please enter formatted IPv4 address : ";
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
    m_flagConnected = m_network.connect(IPaddr, port);
    
}

void RForkliftClient::gui_startClient()
{   
    cout << endl << endl << "CONNECTION TO SERIAL CONTROLLER" << endl;
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
    cout << "Press any key on the keyboard to break the connection and return to the menu" << endl;
    cout << setw(50) << setfill('-') << "-" << endl;

    while(!_kbhit())
    {
        //draw UI
        m_ui.drawArena();
        //m_ui.drawUI();

        bool joypass = false;
        CJoystickPosition analog = m_serial.get_analog(joypass);
        if(joypass)
        {
            if(analog.get_simple_direction() != JOYSTICK_DIRECTION_CENTER)
                cout << "JOYSTICK x= " << analog.getX() << ", y= " << analog.getY() << endl;
            RJoystickEvent joystickEvent(analog);
                m_network.sendEvent(joystickEvent);
        }


        bool button1 = m_serial.get_button(0);
        bool button2 = m_serial.get_button(1);
        bool buttonj1 = m_serial.get_button(5);

        if(button1)
        { 
            cout << "BUTTON1 PRESSED" << endl;
            RControlEvent buttonEvent(ECOMMAND_SET, ETYPE_DIGITAL, 1, 1);
            m_network.sendEvent(buttonEvent);
        }

        if(button2) 
        {
            cout << "BUTTON2 PRESSED" << endl;
            RControlEvent buttonEvent(ECOMMAND_SET, ETYPE_DIGITAL, 2, 1);
            m_network.sendEvent(buttonEvent);
        }

        if(buttonj1)
        {
            cout << "BUTTONJ1 PRESSED" << endl;
            RControlEvent buttonEvent(ECOMMAND_SET, ETYPE_DIGITAL, 5, 1);
            m_network.sendEvent(buttonEvent);
        }
    }   
    cout << "Keypress detected. Disconnecting from server." << endl;
    m_network.disconnect();
    m_flagConnected = false;

    }
   else
   {
    cout << "Invalid response from serial port." << endl;
    return;
   }
    
}
void RForkliftClient::gui_IOTest()
{  
    int serialport;
    prompt("Enter serial port number : ", serialport, "Please enter a number : ", -1);

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
                cout << "JOYSTICK x= " << analog.getX() << ", y= " << analog.getY() << endl;
        }

        
        bool button1 = m_serial.get_button(0);
        bool button2 = m_serial.get_button(1);
        bool buttonj1 = m_serial.get_button(5);

        if(button1) cout << "BUTTON1 PRESSED" << endl;
        if(button2) cout << "BUTTON2 PRESSED" << endl;
        if(buttonj1) cout << "BUTTONJ1 PRESSED" << endl;
    }   
    
    cout << "Keypress detected. Returning to menu..." << endl;
    m_serial.~CControl();
    m_serial = CControl();

   }
   else
   {
    cout << "Invalid response from serial port." << endl;
    return;
   }
}
void RForkliftClient::gui_UITest()
{
    while(!_kbhit())
    {
        //draw UI
        m_ui.drawArena();
        m_ui.drawUI();
    }

    cout << "Keypress detected. Returning to menu..." << endl;
    m_ui.~RDraw();
    m_ui = RDraw();
}