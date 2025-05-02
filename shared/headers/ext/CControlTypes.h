#define CHAR_ARRAY_MAX_SIZE 32 ///< Maximum size for the serial input buffer
#define SERIAL_PORT_DELAY 5 ///< Wait this long (in ms) before checking for a response on the serial bus again
#define SERIAL_PORT_TIMEOUT 2000 ///< Time before the serial monitor times out
#define SERIAL_PORT_CHECK_TO_MAX 15 ///< When finding a port to connect to, check from COM0 to this number

#ifndef BUTTON_DEBOUNCE_TIMEOUT
#define BUTTON_DEBOUNCE_TIMEOUT 50 ///< How long to wait before validating a button press (can be overriden)
#endif

#define BUTTON_NUM_OF_CHANNELS 2 ///< Number of button channels to account for (important for addressing arrays)

#define COM_GET_CHAR "G" ///< Character representing a GET command on the serial bus
#define COM_SET_CHAR "S"///< Character representing a SET command on the serial bus
#define COM_ACK_CHAR "A"///< Character representing an ACK on the serial bus
#define CHAR_LINE_FEED '\n' ///< Represents an LF character literal
#define CHAR_SPACE ' ' ///< Represents a space character literal
#define BLANK_STRING "" ///< Represents a blank string literal

#define COM_CHECK_ALIVE "G -1 0" ///< The "check if alive" message (for seeing if the interface is active)
#define COM_ACK_ALIVE "A -1 0 -1" ///< The expected response to the "check if alive" message

#define CH_SWITCH_S1 0 ///< Switch S1 digital channel number
#define CH_SWITCH_S2 1 ///< Switch S2 digital channel number

#define CH_RGBLED_RED_PIN 2 ///< RED LED digital/analog channel number
#define CH_RGBLED_GRN_PIN 3 ///< GREEN LED digital/analog channel number
#define CH_RGBLED_BLU_PIN 4 ///< BLUE LED digital/analog channel number

#define CH_JOYSTICK_X 0 ///< Joystick X axis analog channel number
#define CH_JOYSTICK_Y 1 ///< Joystick Y axis analog channel number

#define SERVO_PORT0 0 ///< Servo Port 0 servo channel number

using namespace std;

/**
 * @brief Type of command being sent/received
 * 
 */
enum COMMAND_TYPE {COMMAND_GET, COMMAND_SET, COMMAND_ACK};
/**
 * @brief Type of data being sent/received
 * 
 */
enum DATA_TYPE {TYPE_INVALID = -1, TYPE_DIGITAL, TYPE_ANALOG, TYPE_SERVO}; 
