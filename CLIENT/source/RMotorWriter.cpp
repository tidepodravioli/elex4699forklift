#include "../headers/RMotorWriter.hpp"

RMotorWriter::RMotorWriter(RNetClient &client)
{
    m_client = client;
}

void RMotorWriter::write(int leftSpeed, int rightSpeed)
{
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 1, vector<int>({leftSpeed, rightSpeed}));
    m_client.sendEvent(event);
}

void RMotorWriter::drivef(int speed, float distance)
{
    const int comdistance = static_cast<int>(distance * 1000.0f);
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 10, {speed, comdistance});
    m_client.sendEvent(event);

    m_client.waitAck(10000);
}

void RMotorWriter::turn_r(float angle)
{
    const int comangle = static_cast<int>(angle * 1000.0f);
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 12, comangle);
    m_client.sendEvent(event);

    m_client.waitAck(10000);
}

void RMotorWriter::stop()
{
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 1, vector<int>({0, 0}));
    m_client.sendEvent(event);
}

void RMotorWriter::forkWrite(int degrees)
{
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 2, degrees);
    m_client.sendEvent(event);
}

void RMotorWriter::forkUp()
{
    if(fork_index + 1 < FORK_POS_SIZE)
    {
        forkWrite(FORK_POSITIONS[++fork_index]);
    }
}

void RMotorWriter::forkDown()
{
    if(fork_index - 1 > -1)
    {
        forkWrite(FORK_POSITIONS[--fork_index]);
    }
}