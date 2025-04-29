#include "../headers/RPiServo.hpp"

#define FLOOR_POSITION ///< Servo degree value that corresponds with the floor
#define UP_POSITION ///< Servo degree value that corresponds with a rested lifting position
#define UP2_POSITION ///< Servo degree value that corresponds with the second shelf

enum LIFT_POSITION
{
    FLOOR,
    UP,
    UP2
};

class RPiForklift : public RPiServo
{
  private:

  public:
  /**
   * @brief Construct a new RPiForklift object
   * 
   * @param gpioPin PIGPIO pin that the servo is connected to
   */
  RPiForklift(int gpioPin);

  /**
   * @brief Changes the position of the lift
   * 
   * @param position 
   */
  void writePosition(LIFT_POSITION position);
};