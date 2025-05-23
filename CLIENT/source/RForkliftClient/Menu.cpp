#include "../../headers/RForkliftClient.hpp"

using namespace std;
using namespace cv;
using namespace raf_cin;

void RForkliftClient::start()
{
    cli_loadSettingsOnOpen();

    while(true)
    {
        cli_showMenu();

        char option;
        get_char(&option);

        switch(option)
        {
            case '0':
                cli_directCommandTest();
            break;

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

            case '6':
                cli_navToPickupTest();
            break;

            case 'a':
                cli_saveSettings();
            break;

            case 'l':
                cli_loadSettings();
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
    << "(4) UI test" << endl
    << "(5) Motor write test" << endl
    << "(6) Aruco nav test" << endl
    << "(0) Direct server command line" << endl << endl
    << "(a) Save last connection parameters (with debug settings)" << endl
    << "(l) Load last settings" << endl
    << "(s) Settings" << endl
    << "(q) Quit" << endl
    << "> ";
}

void RForkliftClient::cli_saveSettings()
{
    if(prompt_yn("Would you like to save your current settings?"))
    {
        bool loadOnStart = prompt_yn("Would you like your settings to load on start?");

        FileStorage saveFile("settings.yaml", FileStorage::WRITE);
        saveFile << "load-on-start" << loadOnStart;
        saveFile << "ip-address" << m_lastIP;
        saveFile << "port" << m_lastPort;
        saveFile << "require-ccontrol" << m_flagManualAvailable;
        saveFile << "require-frontcam" << m_flagFrontCamNeeded;
        saveFile << "require-overheadcam"<< m_flagArenaCamNeeded;
        
        saveFile.release();

        cout << "Settings saved!" << endl << endl;
    }
}

void RForkliftClient::cli_loadSettings()
{
    FileStorage loadFile("settings.yaml", FileStorage::READ);

    if(loadFile.isOpened())
    {
        loadFile["ip-address"] >> m_lastIP;
        loadFile["port"] >> m_lastPort;
        loadFile["require-ccontrol"] >> m_flagManualAvailable;
        loadFile["require-frontcam"] >> m_flagFrontCamNeeded;
        loadFile["require-overheadcam"] >> m_flagArenaCamNeeded;

        loadFile.release();

        cout << "Settings have been loaded!" << endl << endl;
    }
    else
    {
        cout << "Settings could not be loaded. No changes have been made." << endl << endl;
    }
}

void RForkliftClient::cli_loadSettingsOnOpen()
{
    FileStorage loadFile("settings.yaml", FileStorage::READ);

    if(loadFile.isOpened())
    {
        bool loadOnStart = false;
        loadFile["load-on-start"] >> loadOnStart;

        if(loadOnStart)
        {
            loadFile["ip-address"] >> m_lastIP;
            loadFile["port"] >> m_lastPort;
            loadFile["require-ccontrol"] >> m_flagManualAvailable;
            loadFile["require-frontcam"] >> m_flagFrontCamNeeded;
            loadFile["require-overheadcam"] >> m_flagArenaCamNeeded;

            loadFile.release();

            cout << "Settings have been loaded!" << endl << endl;
        }
    }
}
