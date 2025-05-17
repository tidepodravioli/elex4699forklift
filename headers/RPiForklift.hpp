#pragma once

#include <map>
#include "RPiServo.hpp"

#define FLOOR_POSITION 0 ///< Servo degree value that corresponds with the floor
#define UP_POSITION 0 ///< Servo degree value that corresponds with a rested lifting position
#define FLOOR2_POSITION 0 ///< Servo degree value that corresponds with the second shelf
#define UP2_POSITION 0 ///< Servo degree value that corresponds with the second shelf

enum LIFT_POSITION{ FLOOR, UP, FLOOR2, UP2 };


/**
 * @brief Represents a forklift object controlled by a servo
 * @details RPiForklift inherits from RPiServo to control the up and down
 * motion of the forklift.
 */
class RPiForklift : public RPiServo
{
  private:
  std::map<LIFT_POSITION, int> m_servoPositions;

  public:
  /**
   * @brief Construct a new RPiForklift object
   * 
   * @param gpioPin The pin the servo is connected to
   */
  RPiForklift(int gpioPin);

  /**
   * @brief Changes the position of the lift
   * 
   * @param position 
   */
  void writePosition(LIFT_POSITION position);

  void forkUp();

  void forkDown();
};
