#include "../headers/RMotorDriverF.hpp"

RMotorDriverF::RMotorDriverF(int hL1, int hL2, int hR1, int hR2, int encL1, int encL2, int encR1, int encR2) : RMotorDriver(hL1, hL2, hR1, hR2)
{
    m_encL = new RPiEncoder(encL1, encL2);
    m_encR = new RPiEncoder(encR1, encR2);
}

void RMotorDriverF::drivef(int speed, float distance)
{
    long target_counts = MOTOR_CLICKS_PER_REV * distance / (M_PI * MOTOR_WHEEL_DIAMETER);
    const long startcntL = m_encL->getCount();
    const long startcntR = m_encR->getCount();

    int error, integral, prev_error;
    error = integral = prev_error = 0;

    long countL = 0, countR = 0;

    while (countL < target_counts || countR < target_counts) 
    {
        countL = m_encL->getCount() - startcntL;
        countR = m_encR->getCount() - startcntR;

        // Calculate error
        error = countL - countR;

        // PID terms
        integral += error;
        float derivative = error - prev_error;
        float correction = RMOTORDRIVERF_KP * error + RMOTORDRIVERF_KI * integral + RMOTORDRIVERF_KD * derivative;
        prev_error = error;

        // Apply correction to motor speeds
        int speedA = static_cast<float>(std::clamp(speed - correction, 0.0f, 255.0f));
        int speedB = static_cast<float>(std::clamp(speed + correction, 0.0f, 255.0f));

        write(speedA, speedB);
    }

    stop();
}

void RMotorDriverF::turn_r(float angle) 
{
    float arc_length = abs(angle) * MOTOR_BASE_WIDTH / 2;
    long target_counts = (arc_length / MOTOR_WHEEL_DIAMETER) * MOTOR_CLICKS_PER_REV;

    const long startcntL = m_encL->getCount();
    const long startcntR = m_encR->getCount();

    int error, integral, prev_error;
    error = integral = prev_error = 0;

    long countL = 0, countR = 0;
    while (abs(countL) < target_counts || abs(countR) < target_counts) {
        countL = m_encL->getCount() - startcntL;
        countR = m_encR->getCount() - startcntR;

        // In turning, one count is negative
        error = (countL + countR);

        integral += error;
        float derivative = error - prev_error;
        float correction = RMOTORDRIVERF_KP * error + RMOTORDRIVERF_KI * integral + RMOTORDRIVERF_KD * derivative;
        prev_error = error;

        int speedA = clamp(255 - correction, 0.0f, 255.0f);
        int speedB = clamp(255 + correction, 0.0f, 255.0f);

        if(angle > 0) write(speedA, -speedB);
        else write(-speedA, speedB);
    }

    stop();
}

void RMotorDriverF::turn_d(float angle) 
{
    float deg = angle * M_PI / 180.0f;    
}
