#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;

void RForkliftClient::start()
{
    while(true)
    {
        cli_showMenu();

        char option;
        get_char(&option);

        switch(option)
        {
            case '1':
                cli_startClient();
            break;

            case '2':
                cli_IOTest();
            break;

            case '3':
                cli_streamTest();
            break;

            case '4':
                gui_UITest();
            break;

            case '5':
                cli_antirafTest();
            break;

            case 's':
                cli_settings();
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

void RForkliftClient::cli_showMenu()
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
    << "(2) Serial IO test" << endl
    << "(3) PI Video Stream test" << endl
    << "(4) UI test" << endl << endl
    << "(a) Save last connection parameters (with debug settings)"
    << "(s) Settings" << endl
    << "(q) Quit" << endl
    << "> ";
}
