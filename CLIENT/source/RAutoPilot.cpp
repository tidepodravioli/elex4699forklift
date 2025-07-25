#include "../headers/RAutoPilot.hpp"

RAutoPilot::RAutoPilot(RMotorWriter &driver, RCoordinateHelper &helper) : RMotorWriter(driver)
{
    m_helper = &helper;
}

void RAutoPilot::driveToPoint(cv::Point2i point)
{
    while(true)
    {
        while(!m_helper->refreshRobot() && !m_helper->robotFound());
        cv::Point2i pos = m_helper->getRobotCoords();
        float heading = m_helper->getRobotAngle_r();

        cv::Point2i toTarget = point - pos; //vector from current position to the destination
        float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y); // sqrt(x^2 + y^2)

        //if the robot's distance from the point is within this threshold
        if (distance < POINT_DISTANCE_THRESHOLD) {
            stop(); //the destination can be considered to have been reached
            return;
        }

        float desiredAngle = m_helper->getPointAngle_r(point);
        float angleError = desiredAngle - heading;

        //correcting angle error
        turn_r(angleError);

        const float dx = abs(toTarget.x) * ARENA_WIDTH / ARENA_PXX;
        const float dy = abs(toTarget.y) * ARENA_HEIGHT / ARENA_PYY;

        const float distancem = std::sqrt(dx * dx + dy * dy) - 0.2f;

        drivef(255, distancem);
    }
    stop(); //the destination can be considered to have been reached
}

void RAutoPilot::orientRobot_r(float angle)
{
    float heading = m_helper->getRobotAngle_r();
    float angleError = angle - heading;

    while (angleError > M_PI) angleError -= 2 * M_PI;
    while (angleError < -M_PI) angleError += 2 * M_PI;
    
    if(std::abs(angleError) > 0.15f)
    {
        turn_r(angleError);
    }
    else return;
}

void RAutoPilot::orientRobot_d(float angle)
{
    const float rad = angle * M_PI / 180.0f;
    orientRobot_r(rad);
}

void RAutoPilot::drivePath(vector<cv::Point2i> path)
{
    for(cv::Point2i point : path)
    {
        driveToPoint(point);
    }
}