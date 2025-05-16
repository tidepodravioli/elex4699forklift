#include "../headers/RAutoFork.hpp"

using namespace std;

RAutoFork::RAutoFork(RPiCamera &camera, RCoordinateHelper &helper) {
    m_camera = &camera;
    m_helper = &helper;
}

void RAutoFork::dock()
{
    m_camera->getTranslationClosestTag(m_closest_tag_translation);
    m_closest_tag_angle = atan2(m_closest_tag_translation[2], m_closest_tag_translation[0]);
    if (m_closest_tag_angle < 85) {
        cout << "More to the left" << endl;
    }
    else if (m_closest_tag_angle > 95) {
        cout << "More to the right" << endl;
    } else {
        cout << "Go straight" << endl;
    }
}

void RAutoFork::pickup()
{
}
