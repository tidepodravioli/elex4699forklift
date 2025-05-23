#include <thread>

#include "RMotorDriver.hpp"
#include "RPiEncoder.hpp"

class RMotorDriverF : public RMotorDriver
{
    private:
    RPiEncoder * m_encL, * m_encR;
    int clL = 0, clR = 0;

    bool m_flagDispose = false;
    bool m_flagRun = false;

    public:
    RMotorDriverF(int hL1, int hL2, int hR1, int hR2, int encL1, int encL2, int encR1, int encR2);

    /**
     * @brief BLOCKING! : Drives the specified distance at the given target speed
     * 
     * @param speed The speed to go (-255 to 255)
     * @param distance The distance to go (in meters)
     */
    void drivef(int speed, float distance);

    /**
     * @brief BLOCKING! : Turns the robot in place the specified number of radians
     * 
     * @param angle The angular displacement to turn (negative to the left, positive to the right)
     */
    void turn_r(float angle);

    /**
     * @brief BLOCKING! : Turns the robot in place the specified number of degrees
     * 
     * @param angle The angular displacement to turn (negative to the left, positive to the right)
     */
    void turn_d(float angle);

    
};