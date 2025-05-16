#include "../headers/RAutoFork.hpp"

RAutoFork::RAutoFork(RPiCamera &camera, RCoordinateHelper &helper) {
    m_camera = &camera;
    m_helper = &helper;
}

void RAutoFork::dock()
{
    if (m_camera->getTranslationClosestTag(m_closest_tag_translation)) {
        vector <RArUcoTag3> tags = m_camera->getClosestTags(valid);
        cout << "Tags found: " << tags.size() << endl;
        m_camera->getDistanceClosestTag(m_distance);
        cout << "Distance: " << m_distance << endl;
        m_closest_tag_angle = atan2(m_closest_tag_translation[2], m_closest_tag_translation[0]);
        cout << m_closest_tag_translation[0] << " " << m_closest_tag_translation[1] << " " << m_closest_tag_translation[2] << endl;
        cout << "Closest tag angle: " << m_closest_tag_angle << endl;
        if (m_closest_tag_angle < 85) {
            cout << "More to the left" << endl;
        }
        else if (m_closest_tag_angle > 95) {
            cout << "More to the right" << endl;
        } else {
            cout << "Go straight" << endl;
        }
    } else {
        cout << "No tags found" << endl;
    }
}

void RAutoFork::pickup()
{
    
}
