#pragma once

#include "RPiServo.hpp"

class RPiForklift : public RPiServo
{
  private:

  public:
  RPiForklift(int gpioPin) : RPiServo(gpioPin) {}

  /**
   * @brief Changes the position of the lift
   * 
   * @param position 
   */
  void writePosition(int position);
};