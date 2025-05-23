#pragma once
#include "RNetClient.hpp"
#define FORK_POS_SIZE 6

class RMotorWriter
{
    private:
    RNetClient m_client;

    const int FORK_POSITIONS[FORK_POS_SIZE] = {165, 150, 97, 82, 30, 15};
    int fork_index = 0;

    public:
    RMotorWriter(RNetClient &client);

    void write(int leftSpeed, int rightSpeed);

    void drivef(int speed, float distance);

    void turn_r(float angle);

    void forkUp();

    void forkDown();

    void forkWrite(int angle);

    void forkSet(int index);

    int forkIndex() {return fork_index;}

    void stop();
};