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
    float robot_wheel_base_cm = 20.0; // distance between wheels
    float arc_length = (deg / 360.0) * (robot_wheel_base_cm * 3.1416);
    long target_counts = (arc_length / wheel_circumference_cm) * counts_per_rev;

    countA = 0; countB = 0;
    error = integral = prev_error = 0;

    while (abs(countA) < target_counts || abs(countB) < target_counts) {
    // In turning, one count is negative
    error = (countA + countB);

    integral += error;
    float derivative = error - prev_error;
    float correction = Kp * error + Ki * integral + Kd * derivative;
    prev_error = error;

    int speedA = constrain(base_speed - correction, 0, 255);
    int speedB = constrain(base_speed + correction, 0, 255);

    // Left wheel backward
    analogWrite(ENA, speedA);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);

    // Right wheel forward
    analogWrite(ENB, speedB);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    }

    stopMotors();
}
