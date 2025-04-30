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

void RNetServer::awaitCom(string &command)
{
    string _command;
    
    while(!getCom(_command));

    command = _command;
}

bool RNetServer::getCom(string &command)
{
    vector<string> commands;
    m_server.get_cmd(commands);
    command = commands[0];

    return !commands[0].empty();
}