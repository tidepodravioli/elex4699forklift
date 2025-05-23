#include "../headers/RMotorDriver.hpp"
#include <algorithm>

// template <typename T>
// T clamp(T val, T minVal, T maxVal) {
//     return std::max(minVal, std::min(val, maxVal));
// }

RMotorDriver::RMotorDriver(int left1, int left2, int right1, int right2)
{
    m_leftMotor = new RPiHMotor(left1, left2);
    m_rightMotor = new RPiHMotor(right1, right2);
}

void RMotorDriver::write(int leftSpeed, int rightSpeed)
{
    m_leftMotor->motorWrite(leftSpeed);
    m_rightMotor->motorWrite(rightSpeed);
}

void RMotorDriver::joystickDrive(int pX, int pY)
{
    int spX, spY;
    arcadeDrive(pX, pY, spX, spY);
    write(spX, spY);
    cout << spX << setw(10) << spY << endl;
}

void RMotorDriver::drive(int speed, bool useOffset)
{
    const int leftSpeed = speed + useOffset? LEFT_MOTOR_SPEED_OFFSET : 0;
    const int rightSpeed = speed + useOffset? RIGHT_MOTOR_SPEED_OFFSET : 0;

    write(leftSpeed, rightSpeed);
}

void RMotorDriver::slowMode()
{
    m_flagSlowMode = true;
    m_topSpeedPWM = SLOW_SPEED_PWM;
}

void RMotorDriver::normalMode()
{
    m_flagSlowMode = false;
    m_topSpeedPWM = TOP_SPEED_PWM;
}

bool RMotorDriver::toggleSlow()
{
    m_flagSlowMode = !m_flagSlowMode;
    if(m_flagSlowMode) slowMode();
    else normalMode();

    return m_flagSlowMode;
}

void RMotorDriver::forward()
{
   drive(255, true);
}

void RMotorDriver::backward()
{
   drive(-255, true);
}

void RMotorDriver::left()
{
    const int leftSpeed = 255 + LEFT_MOTOR_SPEED_OFFSET;
    const int rightSpeed = 255 + RIGHT_MOTOR_SPEED_OFFSET;

    write(-leftSpeed, rightSpeed);
}

void RMotorDriver::right()
{
    const int leftSpeed = 255 + LEFT_MOTOR_SPEED_OFFSET;
    const int rightSpeed = 255 + RIGHT_MOTOR_SPEED_OFFSET;

    write(leftSpeed, -rightSpeed);
}

void RMotorDriver::stop()
{
    drive(0);
}

void RMotorDriver::turnLeft(int speed)
{
    if(speed > 0)
    {
        const int leftSpeed = speed + LEFT_MOTOR_SPEED_OFFSET;
        const int rightSpeed = speed + RIGHT_MOTOR_SPEED_OFFSET;

        write(-leftSpeed, rightSpeed);
    }
}

void RMotorDriver::turnRight(int speed)
{
    if(speed > 0)
    {
        const int leftSpeed = speed + LEFT_MOTOR_SPEED_OFFSET;
        const int rightSpeed = speed + RIGHT_MOTOR_SPEED_OFFSET;

        write(leftSpeed, -rightSpeed);
    }
}

// Helper: Map joystick [0–100] to [-1.0 to +1.0] with deadzone and cubic curve
float RMotorDriver::processAxis(int raw) {
    float centered = static_cast<float>(raw) - RMOTORDRIVER_JOYSTICK_CENTER;

    // Apply deadzone
    if (std::abs(centered) < RMOTORDRIVER_DEADZONE)
        return 0.0f;

    // Normalize to [-1, 1]
    float norm = centered / RMOTORDRIVER_MAX_INPUT;

    // Apply cubic scaling for smoother response
    float curved = norm * norm * norm;

    return curved;
}

// Main drive mixer
void RMotorDriver::arcadeDrive(int joyX, int joyY, int& leftMotor, int& rightMotor) {
    float fwd = processAxis(joyY); // Forward/backward
    float turn = processAxis(joyX); // Left/right

    // Mix drive and turn
    float left = fwd + turn;
    float right = fwd - turn;

    // Clamp to [-1, 1]
    left = clamp(left, -1.0f, 1.0f);
    right = clamp(right, -1.0f, 1.0f);

    // Scale to motor range
    leftMotor = static_cast<int>(left * m_topSpeedPWM);
    rightMotor = static_cast<int>(right * m_topSpeedPWM);
}