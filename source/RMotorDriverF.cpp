#include "../headers/RMotorDriverF.hpp"

RMotorDriverF::RMotorDriverF(int hL1, int hL2, int hR1, int hR2, int encL1, int encL2, int encR1, int encR2) : RMotorDriver(hL1, hL2, hR1, hR2)
{
    m_encL = new RPiEncoder(encL1, encL2);
    m_encR = new RPiEncoder(encR1, encR2);
}

void RMotorDriverF::drivef(int speed, float distance)
{
    std::cout << "DISTANCE" << distance << endl;
    long target_counts = MOTOR_CLICKS_PER_REV * distance / (M_PI * MOTOR_WHEEL_DIAMETER);
    const long startcntL = m_encL->getCount();
    const long startcntR = m_encR->getCount();

    int error, integral, prev_error;
    error = integral = prev_error = 0;

    long countL = 0, countR = 0;

    // while (abs(countL) < target_counts || abs(countR) < target_counts) 
    // {
    //     countL = abs(m_encL->getCount() - startcntL);
    //     countR = abs(m_encR->getCount() - startcntR);

    //     std::cout << "COUNT : " << countL << ", " << countR << endl;
    //     // Calculate error
    //     error = countL - countR;

    //     // PID terms
    //     integral += error;
    //     float derivative = error - prev_error;
    //     float correction = m_kp * error + m_ki * integral + m_kd * derivative;
    //     prev_error = error;

    //     // Apply correction to motor speeds
    //     int speedA = static_cast<float>(std::clamp(speed - correction, 0.0f, 255.0f));
    //     int speedB = static_cast<float>(std::clamp(speed + correction, 0.0f, 255.0f));

    //     write(speedA, speedB);
    //     usleep(5000);
    // }

    bool left_done = false;
    bool right_done = false;

   while (!left_done || !right_done) 
   {
        int countL = m_encL->getCount() - startcntL;
        int countR = m_encR->getCount() - startcntR;

        if (countL >= target_counts) left_done = true;
        if (countR >= target_counts) right_done = true;

        float correction = 0.0f;

        if (!left_done && !right_done) {
            error = countL - countR;
            integral += error;
            float derivative = error - prev_error;
            correction = m_kp * error + m_ki * integral + m_kd * derivative;
            prev_error = error;
        }

        int speedA = left_done  ? 0 : std::clamp((int)(speed - correction), 0, 255);
        int speedB = right_done ? 0 : std::clamp((int)(speed + correction), 0, 255);

        write(speedA, speedB);
        usleep(1000); // let encoder ISR update
    }


    stop();
}

void RMotorDriverF::turn_r(float angle) 
{
    float arc_length = abs(angle) * MOTOR_BASE_WIDTH / 2.0f;
    long target_counts = (arc_length / (MOTOR_WHEEL_DIAMETER * M_PI)) * MOTOR_CLICKS_PER_REV;

    const long startcntL = m_encL->getCount();
    const long startcntR = m_encR->getCount();

    int error = 0, integral = 0, prev_error = 0;

    long countL = 0, countR = 0;
    while (true) {
        countL = m_encL->getCount() - startcntL;
        countR = m_encR->getCount() - startcntR;

        // Use average progress of both wheels
        long avg_count = (countL + countR) / 2;
        if (avg_count >= target_counts) break;

        // PID to keep wheels in sync
        error = (countL - countR);  // Positive if left is ahead
        integral += error;
        int derivative = error - prev_error;
        float correction = m_kp * error + m_ki * integral + m_kd * derivative;
        prev_error = error;

        int base_speed = 255;
        int speedL = clamp(base_speed - correction, 0.0f, 255.0f);
        int speedR = clamp(base_speed + correction, 0.0f, 255.0f);

        if (angle > 0) {
            // Turn right: Left forward, Right stationary or slower
            write(speedL, -speedR);
        } else {
            // Turn left: Left stationary or slower, Right forward
            write(-speedL, speedR);
        }
    }

    stop();
}


void RMotorDriverF::turn_d(float angle) 
{
    float deg = angle * M_PI / 180.0f;    
    turn_r(deg);
}
