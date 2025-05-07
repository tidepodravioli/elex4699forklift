#include "../headers/RAutoPilot.hpp"


RAutoPilot::RAutoPilot(RMotorDriver &driver, RCoordinateHelper &helper) : RMotorDriver(driver)
{
    m_driver = &driver;
    m_helper = &helper;

}

void RAutoPilot::driveToPoint(Point2i point)
{
    while (true) {
        Point2i pos = m_helper->getRobotCoords();
        float heading = m_helper->getRobotAngle() * 3.14159f / 180.0f; // In radians

        cv::Point2i toTarget = point - pos;
        float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

        if (distance < POINT_DISTANCE_THRESHOLD) {
            m_driver->stop();
            return;
        }

        float desiredAngle = std::atan2(toTarget.y, toTarget.x);

        float angleError = desiredAngle - heading;
        while (angleError > M_PI) angleError -= 2 * M_PI;
        while (angleError < -M_PI) angleError += 2 * M_PI;

        if (std::abs(angleError) > 1.0f) {
            float turnSpeed = std::clamp(angleError * ANGLE_GAIN, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            m_driver->write(-turnSpeed, turnSpeed);
        } else {
            float correction = angleError * ANGLE_GAIN;
            float left = std::clamp(MAX_AUTO_SPEED - correction, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            float right = std::clamp(MAX_AUTO_SPEED + correction, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            m_driver->write(left, right);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(DRIVE_CORRECTION_COOLDOWN));
    }
}