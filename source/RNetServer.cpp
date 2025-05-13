#include "../headers/RNetServer.hpp"

RNetServer::RNetServer()
{
    
}

void RNetServer::startServer(int port)
{
    // starts listening on the given port
    thread server_t(&RNetServer::server_start, this, port);
    server_t.detach();
}

void RNetServer::server_start(int port)
{
    start(port);
}

void RNetServer::stopServer()
{
    stop();
}

bool RNetServer::getCom(vector<string> &commands)
{
    vector<string> _commands;
    get_cmd(_commands);
    
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
            _events.push_back(RControlEvent::parse(command));
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
    send_string(command);
}