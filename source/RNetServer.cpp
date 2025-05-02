#include "../headers/RNetServer.hpp"

void RNetServer::startServer(int port)
{
    thread server_t(&RNetServer::server_start, this, port);
    server_t.detach();
}

void RNetServer::server_start(int port)
{
    m_server.start(port);
}

void RNetServer::stopServer()
{
    m_server.stop();
}

bool RNetServer::getCom(vector<string> &commands)
{
    vector<string> _commands;
    m_server.get_cmd(_commands);
    commands = _commands;

    return !commands.empty();
}

bool RNetServer::getCom(vector<RControlEvent> &events)
{
    vector<string> commands;
    vector<RControlEvent> _events;
    if(getCom(commands))
    {
        for(string command : commands)
        {
            _events.push_back(RControlEvent(command));
        }

        events = _events;
        return true;
    }
    else
    {
        return false;
    }

}

void RNetServer::sendCom(string command)
{
    m_server.send_string(command);
}