#include "../headers/RAutoPilot.hpp"

RAutoPilot::RAutoPilot(RMotorWriter &driver, RCoordinateHelper &helper) : RMotorWriter(driver)
{
    m_helper = &helper;
}

void RAutoPilot::driveToPoint(cv::Point2i point)
{
    while (true) {
        //Get robot's current position and angle
        cv::Point2i pos = m_helper->getRobotCoords();
        float heading = m_helper->getRobotAngle_r(); // In radians

        cout << "Heading : " << heading << endl;

        cout << "Robot at : " << pos << endl;

        cv::Point2i toTarget = point - pos; //vector from current position to the destination
        float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y); // sqrt(x^2 + y^2)

        //if the robot's distance from the point is within this threshold
        if (distance < POINT_DISTANCE_THRESHOLD) {
            cout << "destination reached" << endl;
            stop(); //the destination can be considered to have been reached
            return;
        }

        //otherwise, continue

        float desiredAngle = m_helper->getPointAngle_r(point); //the angle that the line between the robot's position and the destination makes with the x-axis

        cout << "Desired angle : " << desiredAngle << endl;

        float angleError = desiredAngle - heading; //how far off we are from the wanted angle

        //normalize the angleError between -180 and +180 degrees (-pi to pi radians)
        while (angleError > M_PI) angleError -= 2 * M_PI;
        while (angleError < -M_PI) angleError += 2 * M_PI;


        if (std::abs(angleError) > 1.0f) {
            cout << "correcting heading" << endl;
            float turnSpeed = std::clamp(angleError * ANGLE_GAIN, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            write(turnSpeed, -turnSpeed);
        } else {
            cout << "moving straight" << endl;
            float correction = angleError * ANGLE_GAIN;
            float left = std::clamp(MAX_AUTO_SPEED - correction, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            float right = std::clamp(MAX_AUTO_SPEED + correction, -MAX_AUTO_SPEED, MAX_AUTO_SPEED);
            write(left, right);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(DRIVE_CORRECTION_COOLDOWN));
    }
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