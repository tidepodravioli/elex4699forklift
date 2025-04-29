#include "../headers/RForkliftManager.hpp"

void RForkliftManager::start()
{
    m_leftMotor = new RPiHMotor(MOTOR_L1, MOTOR_L2);
    m_leftMotor = new RPiHMotor(MOTOR_R1, MOTOR_R2);
}