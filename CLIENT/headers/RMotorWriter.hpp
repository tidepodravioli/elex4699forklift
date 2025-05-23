#pragma once
#include "RNetClient.hpp"

class RMotorWriter
{
    private:
    RNetClient m_client;

    public:
    RMotorWriter(RNetClient &client);

    void write(int leftSpeed, int rightSpeed);

    void drivef(int speed, float distance);

    void turn_r(float angle);

    void stop();
};