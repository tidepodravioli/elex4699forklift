/**
 * @file CJoystickPosition.hpp
 * @author Rafael Banalan  A01367816 4S (abanalan@my.bcit.ca)
 * @brief 
 * @version 0.1
 * @date 2025-02-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#define JOYSTICK_X_MIN 107 ///< Minimum joystick analog x value
#define JOYSTICK_X_MAX 920 ///< Maximum joystick analog x value

#define JOYSTICK_Y_MIN 140 ///< Minimum joystick analog x value
#define JOYSTICK_Y_MAX 984 ///< Maximum joystick analog x value



/**
 * @name JOYSTICK_IGNORE
 * @brief JOYSTICK_IGNORE_LRVP and JOYSTICK_IGNORE_LRVP define the range 
 * (as percentages) at which get_direction() will ignore the input 
 * of either x or y.
 * 
 * For example, if percentX() is 47% with LRVP=40% and URVP=60%,
 * x would be ignored and treated as if it was resting when evaluating
 * the direction it is going. If get_direction() was evaluating for a 
 * NORTH direction, percentX() would need to be at this range, and
 * percentY() would need to be higher than the URVP.
 * @{
 */

#ifndef JOYSTICK_IGNORE_LRVP
    #define JOYSTICK_IGNORE_LRVP 40 ///< The lower end of the ignore range (see docs)
#endif

#ifndef JOYSTICK_IGNORE_URVP
    #define JOYSTICK_IGNORE_URVP 60 ///< The upper end of the ignore range (see docs)
#endif
/** @}*/

/**
 * @brief Represents the directions that the joystick can be going in
 * 
 */
enum JOYSTICK_DIRECTION 
{
    JOYSTICK_DIRECTION_NORTH, 
    JOYSTICK_DIRECTION_NORTHEAST,  
    JOYSTICK_DIRECTION_EAST, 
    JOYSTICK_DIRECTION_SOUTHEAST, 
    JOYSTICK_DIRECTION_SOUTH, 
    JOYSTICK_DIRECTION_SOUTHWEST,
    JOYSTICK_DIRECTION_WEST,
    JOYSTICK_DIRECTION_NORTHWEST,
    JOYSTICK_DIRECTION_CENTER
};

/**
 * @brief Represents a joysticks position in terms of its raw analog value on both axes
 * 
 */
class CJoystickPosition
{
private:
    /**
     * @brief The raw analog value of the x-axis on the joystick
     * 
     */
    int m_joystickx;

    /**
     * @brief The raw analog value of the y-axis on the joystick
     * 
     */
    int m_joysticky;

    /**
     * @brief Checks to see whether a number is in a range
     * 
     * @param input the number being checked
     * @param min the lowest end of the range
     * @param max the highest end of the range
     * @return true if input is inside the range
     * @return false if input is outside the range
     */
    bool withinValues(int input, int min, int max);
public:
    CJoystickPosition();
    /**
     * @brief Construct a new CJoystickPosition object
     * 
     * @param x 
     * @param y 
     */
    CJoystickPosition(int x, int y);
    
    /**
     * @brief Destroy the CJoystickPosition object
     * 
     */
    ~CJoystickPosition();

    /**
     * @brief Gets the stored joystick x-axis analog value
     * 
     * @return int The raw analog value as read from the x-axis
     */
    int getX();

    /**
     * @brief Gets the stored joystick y-axis analog value
     * 
     * @return int The raw analog value as read from the y-axis
     */
    int getY();
    
    /**
     * @brief Calculates what percent of the full range the x-axis is
     * 
     * @return int 
     */
    int percentX();
    int percentY();

    /**
     * @brief Gets the implied direction of the joystick
     * 
     * @return JOYSTICK_DIRECTION direction based on x and y percentages and given threshholds
     */
    JOYSTICK_DIRECTION get_direction();

    JOYSTICK_DIRECTION get_simple_direction();

    /**
     * @brief Get the opposite of the implied direction of the joystick.
     * 
     * @return JOYSTICK_DIRECTION the opposite direction given by get_direction().
     * Returns JOYSTICK_DIRECTION_CENTER if JOYSTICK_DIRECTION_CENTER is the implied direction.
     */
    JOYSTICK_DIRECTION get_opposite_direction();

    JOYSTICK_DIRECTION get_simple_opposite();
};

namespace direction_op
{
    JOYSTICK_DIRECTION get_opposite_direction(JOYSTICK_DIRECTION input);
}