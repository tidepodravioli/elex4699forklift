#include "../headers/RForkliftManager.hpp"

void RForkliftManager::registerCommands()
{
    m_commandHandlers[{ECOMMAND_SET, ETYPE_DIGITAL}] = [](const RControlEvent &cmd)
    {
        const vector<string> vals = cmd.getValues();
        vector<bool> bvecs;
        for(string dat : vals)
        {
            if(dat == "1") bvecs.push_back(true);
            else bvecs.push_back(false);
        }

        com_setDigital(cmd.getOrigin(), bvecs);
    };

    m_commandHandlers[{ECOMMAND_SET, ETYPE_ANALOG}] = [](const RControlEvent &cmd)
    {
        com_setAnalog(cmd.getOrigin(), cmd.getIntValues());
    };

    m_commandHandlers[{ECOMMAND_SET, ETYPE_COMMAND}] = [](const RControlEvent &cmd)
    {
        com_setCommand(cmd.getOrigin(), cmd.getValues());
    };

    m_commandHandlers[{ECOMMAND_GET, ETYPE_COMMAND}] = [](const RControlEvent &cmd)
    {
        com_getCommand(cmd.getOrigin(), cmd.getValues());
    };
}

void RForkliftManager::handleCommand(const RControlEvent& cmd) {
    CommandKey key = { cmd.getCom(), cmd.getType() };
    auto it = commandHandlers.find(key);
    if (it != commandHandlers.end()) {
        it->second(cmd);
    } else {
        std::cerr << "Unhandled command combination: " << cmd.commandType << " " << cmd.dataType << '\n';
    }
}

void RForkliftManager::com_setAnalog(int origin, vector<int> values)
{
    switch(origin)
    {
        case 0: // JOYSTICK DRIVE WRITE
        cout << "JOYSTICK EVENT" << endl;
        m_driver->joystickDrive(values[0], values[1]);
        break;

        case 1: // DIRECT SPEED WRITE
        cout << "DIRECT SPEED WRITE" << endl;
        m_driver->write(values[0], values[1]);
        break;

        // Do nothing if the channel isn't found
        default:
        break;
    }
}

void RForkliftManager::com_setCommand(int origin, vector<string> values)
{
    switch(origin)
    {
        case 2: // CAMERA SETUP
        vector<string> IPs;
        m_server.get_connected_ips(IPs);

        const string IPaddr = IPs[0];
        const int port = stoi(values[0]);

        m_stream = new RVidStream();
        m_stream->target(IPaddr, port);
        m_stream->stream(m_camera);

        m_frontCamIP = IPaddr;
        m_frontCamPort - port;
        break;

        // Do nothing if the channel isn't found
        default:
        break;
    }
}

void RForkliftManager::com_getCommand(int origin, vector<string> values)
{
    switch(origin)
    {
        case 0: // HEARTBEAT/HANDSHAKE
        RControlEvent heartbeat = current.copy();
        heartbeat.setCom(ECOMMAND_ACK);
        m_server.sendCom(heartbeat.asCommand());
        break;

        case 2: // GET CAM CONFIG (for confirmation by client)
        RControlEvent camConfig(ECOMMAND_ACK, ETYPE_COMMAND, 2, {m_frontCamIP, to_string(m_frontCamPort)});
        m_server.sendCom(camConfig.asCommand());
        break;

        // Do nothing if the channel isn't found
        default:
        break;
    }
}

void RForkliftManager::com_setDigital(int origin, vector<bool> values)
{
    switch(origin)
    {
        case 0: // FORK UP
        if(values[0]) m_forklift->forkUp();
        break;
        
        case 1: // FORK DOWN
        if(values[0]) m_forklift->forkDown();
        break;

        case 2:
        m_driver->toggleSlow();
        break;

        // Do nothing if the channel isn't found
        default:
        break;
    }
}