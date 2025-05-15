#include "../headers/RMotorWriter.hpp"

RMotorWriter::RMotorWriter(RNetClient &client)
{
    
}

void RMotorWriter::write(int leftSpeed, int rightSpeed)
{
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 1, vector<int>({leftSpeed, rightSpeed}));
    sendEvent(event);
}

void RMotorWriter::stop()
{
    RControlEvent event = RControlEvent(ECOMMAND_SET, ETYPE_ANALOG, 1, vector<int>({0, 0}));
    sendEvent(event);
}