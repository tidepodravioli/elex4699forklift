#include "../headers/RAutoFork.hpp"

RAutoFork::RAutoFork(&RPiCamera &camera, &RAutoPilot &autopilot, &RCoordinateHelper &helper, &RPiForklift &forklift) {
    m_camera = &camera;
    m_autopilot = &autopilot;
    m_helper = &helper;
    m_forklift = &forklift;;
}

void RAutoFork::approachPackage()
{
    m_closest_tag = m_camera->getClosestTags().at(0);
    m_packageCoords = m_helper->getTagCoords(m_closest_tag);
    m_autopilot->driveToPoint(m_packageCoords);
}

void RAutoFork::pickUpPackage()
{
    m_forklift->writePosition(FORKLIFT_1_UP);

    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < m_backupTime) {
        m_autopilot->write(-SLOW_SPEED_PWM, -SLOW_SPEED_PWM);
    }
}

void RAutoFork::driveToDropOff()
{
    for (int i = 0; i < size(m_dropOffCoords); i++) {
        m_autopilot->driveToPoint(m_dropOffCoords.at(i));
    }
}

void RAutoFork::dropOffPackage()
{
    m_forklift->writePosition(FORKLIFT_1_DOWN);

    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < m_backupTime) {
        m_autopilot->write(-SLOW_SPEED_PWM, -SLOW_SPEED_PWM);
    }
}

void RAutoFork::reset()
{
    // Do a little dance (just for today)
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < 1) {
        m_autopilot->write(255, -255);
    }

    m_forklift->writePosition(FORKLIFT_2_UP);
    m_forklift->writePosition(FORKLIFT_1_DOWN);
}

void RAutoFork::run()
{
    approachPackage();
    pickUpPackage();
    driveToDropOff();
    dropOffPackage();
    reset();
}