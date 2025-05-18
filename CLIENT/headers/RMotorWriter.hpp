#pragma once
#include "RNetClient.hpp"

class RMotorWriter
{
    private:
    RNetClient m_client;

    public:
    RMotorWriter(RNetClient &client);

    void write(int leftSpeed, int rightSpeed);

    void stop();
};