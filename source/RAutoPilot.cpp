#include "../headers/RAutoPilot.hpp"

RAutoPilot::RAutoPilot(RMotorDriver &driver, RCoordinateHelper &helper) : RMotorDriver(driver)
{
    m_driver = &driver;
    m_helper = &helper;

}

void RAutoPilot::driveToPoint(Point2i point)
{
    while (true) {
        //Get robot's current position and angle
        Point2i pos = m_helper->getRobotCoords();
        float heading = m_helper->getRobotAngle_r(); // In radians

        cv::Point2i toTarget = point - pos; //vector from current position to the destination
        float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y); // sqrt(x^2 + y^2)

        //if the robot's distance from the point is within this threshold
        if (distance < POINT_DISTANCE_THRESHOLD) {
            m_driver->stop(); //the destination can be considered to have been reached
            return;
        }

        //otherwise, continue

        float desiredAngle = m_helper->getPointAngle_r(point); //the angle that the line between the robot's position and the destination makes with the x-axis

        float angleError = desiredAngle - heading; //how far off we are from the wanted angle

        //normalize the angleError between -180 and +180 degrees (-pi to pi radians)
        while (angleError > M_PI) angleError -= 2 * M_PI;
        while (angleError < -M_PI) angleError += 2 * M_PI;


        if (std::abs(angleError) > 1.0f) {
            float turnSpeed = std::clamp(angleError * ANGLE_GAIN, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            write(turnSpeed, -turnSpeed);
        } else {
            float correction = angleError * ANGLE_GAIN;
            float left = std::clamp(MAX_AUTO_SPEED - correction, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            float right = std::clamp(MAX_AUTO_SPEED + correction, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            write(left, right);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(DRIVE_CORRECTION_COOLDOWN));
    }
}

void RAutoPilot::orientRobot(float angle)
{
    while(true)
    {
        float heading = m_helper->getRobotAngle_r();
        float angleError = angle - heading;

        while (angleError > M_PI) angleError -= 2 * M_PI;
        while (angleError < -M_PI) angleError += 2 * M_PI;

        if(std::abs(angleError) > 0.15f)
        {
            float turnSpeed = std::clamp(angleError * ANGLE_GAIN, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            write(turnSpeed, -turnSpeed);
        }
        else return;
    }
}

void RAutoPilot::drivePath(vector<Point2i> path)
{
    for(Point2i point : path)
    {
        driveToPoint(point);
    }
}