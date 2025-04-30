#include "../headers/RForkliftManager.hpp"

void RForkliftManager::start()
{
    m_driver = new RMotorDriver(MOTOR_L1, MOTOR_L2, MOTOR_R1, MOTOR_R2);
    m_forklift = new RPiForklift(FORKLIFT_SERVO);

    
}