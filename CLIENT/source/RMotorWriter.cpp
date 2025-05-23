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
}

void RMotorWriter::turn_r(float angle)
{
    const int comangle = static_cast<int>(angle * 1000.0f);
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 12, angle);
    m_client.sendEvent(event);
}

void RMotorWriter::stop()
{
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 1, vector<int>({0, 0}));
    m_client.sendEvent(event);
}