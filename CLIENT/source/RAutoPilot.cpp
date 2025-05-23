#include "../headers/RAutoPilot.hpp"

RAutoPilot::RAutoPilot(RMotorWriter &driver, RCoordinateHelper &helper) : RMotorWriter(driver)
{
    m_helper = &helper;
}

void RAutoPilot::driveToPoint(cv::Point2i point)
{
    while(m_helper->refreshRobot() && m_helper->robotFound());
    cv::Point2i pos = m_helper->getRobotCoords();
    float heading = m_helper->getRobotAngle_r();

    cv::Point2i toTarget = point - pos; //vector from current position to the destination
    float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y); // sqrt(x^2 + y^2)

    //if the robot's distance from the point is within this threshold
    if (distance < POINT_DISTANCE_THRESHOLD) {
        cout << "Destination reached" << endl;
        stop(); //the destination can be considered to have been reached
        return;
    }

    float desiredAngle = m_helper->getPointAngle_r(point);
    float angleError = desiredAngle - heading;

    turn_r(angleError);

    const int dx = abs(toTarget.x) * ARENA_WIDTH / ARENA_PXX;
    const int dy = abs(toTarget.y) * ARENA_HEIGHT / ARENA_PYY;

    const float distance = norm(cv::Point2f(dx, dy));

    drivef(255, distance);
    
}

void RAutoPilot::orientRobot_r(float angle)
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

void RAutoPilot::orientRobot_d(float angle)
{
    const float rad = M_PI / 180.0f;
    orientRobot_r(rad);
}

void RAutoPilot::drivePath(vector<cv::Point2i> path)
{
    for(cv::Point2i point : path)
    {
        driveToPoint(point);
    }
}