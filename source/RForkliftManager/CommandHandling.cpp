#include "../headers/RForkliftManager.hpp"

void RForkliftManager::registerCommands()
{
    m_commandHandlers[{ECOMMAND_SET, ETYPE_DIGITAL}] = [](RForkliftManager * manager, RControlEvent &cmd)
    {
        const vector<string> vals = cmd.getValues();
        vector<bool> bvecs;
        for(string dat : vals)
        {
            if(dat == "1") bvecs.push_back(true);
            else bvecs.push_back(false);
        }

        return manager->com_setDigital(cmd.getOrigin(), bvecs);
    };

    m_commandHandlers[{ECOMMAND_SET, ETYPE_ANALOG}] = [](RForkliftManager * manager, RControlEvent &cmd)
    {
        return manager->com_setAnalog(cmd.getOrigin(), cmd.getIntValues());
    };

    m_commandHandlers[{ECOMMAND_SET, ETYPE_COMMAND}] = [](RForkliftManager * manager, RControlEvent &cmd)
    {
        return manager->com_setCommand(cmd.getOrigin(), cmd.getValues());
    };

    m_commandHandlers[{ECOMMAND_GET, ETYPE_COMMAND}] = [](RForkliftManager * manager, RControlEvent &cmd)
    {
        return manager->com_getCommand(cmd.getOrigin(), cmd.getValues());
    };
}

void RForkliftManager::handleCommand(RControlEvent& cmd) {
    CommandKey key = { cmd.getCom(), cmd.getType() };
    auto it = m_commandHandlers.find(key);
    if (it != m_commandHandlers.end()) {
        bool sendAck = it->second(this, cmd);
        if(sendAck)
        {
            RControlEvent ack = cmd.copy();
            ack.setCom(ECOMMAND_ACK);
            m_server.sendCom(ack);
        }
    } else {
        std::cerr << "Unhandled command combination: " << cmd.getCom() << " " << cmd.getType() << '\n';
    }
}

bool RForkliftManager::com_setAnalog(int origin, vector<int> values)
{
    switch(origin)
    {
        case 0: // JOYSTICK DRIVE WRITE
        {
            cout << "JOYSTICK EVENT" << endl;
            m_driver->joystickDrive(values[0], values[1]);
            break;
        }
        case 1: // DIRECT SPEED WRITE
        {
            cout << "DIRECT SPEED WRITE" << endl;
            m_driver->write(values[0], values[1]);
            break;
        }
        case 2:
        {
            m_forklift->write(values[0]);
            break;
        }

        case 10:
        {
            float distance = values[1] / 1000.0f;
            m_driver->drivef(values[0], distance);
            return true;
            break;
        }

        case 11:
        {
            const float angle = values[0];
            m_driver->turn_d(angle);
            return true;
            break;
        }

        case 12:
        {
            const float angle = values[0] / 1000.0f;
            m_driver->turn_r(angle);
            break;
        }

        case 110:
        {
            const float kp = values[0] / 1000.0f;
            m_driver->setkp(kp);
            break;
        }

        case 111:
        {
            const float ki = values[0] / 1000.0f;
            m_driver->setki(ki);
            break;
        }

        case 112:
        {
            const float kd = values[0] / 1000.0f;
            m_driver->setkd(kd);
            break;
        }

        default:
        cout << "Unrecognized channel..." << endl;
        break;
    }

    return false;
}

bool RForkliftManager::com_setCommand(int origin, vector<string> values)
{
    switch(origin)
    {
        case 2: // CAMERA SETUP
        {
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
        }

        default:
        cout << "Unrecognized channel..." << endl;
        break;
    }

    return false;
}

bool RForkliftManager::com_getCommand(int origin, vector<string> values)
{
    switch(origin)
    {
        case 0: // HEARTBEAT/HANDSHAKE
        {
            RControlEvent heartbeat(ECOMMAND_ACK, ETYPE_COMMAND, 0, values);
            m_server.sendCom(heartbeat.asCommand());
            break;
        }
        case 2: // GET CAM CONFIG (for confirmation by client)
        {
            RControlEvent camConfig(ECOMMAND_ACK, ETYPE_COMMAND, 2, {m_frontCamIP, to_string(m_frontCamPort)});
            m_server.sendCom(camConfig.asCommand());
            break;
        }

        default:
        cout << "Unrecognized channel..." << endl;
        break;
    }

    return false;
}

bool RForkliftManager::com_setDigital(int origin, vector<bool> values)
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

        default:
        cout << "Unrecognized channel..." << endl;
        break;
    }

    return false;
}