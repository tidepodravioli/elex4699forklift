# TIVA Firmware
This firmware is prepared for the TI TM4C123GH6PM Launchpad (EK-TM4C123GXL) for use with the CControl library as included in this project.

It provides GET, SET, and ACK based communication between the client program and the microcontroller and serves as the main method of input control to the manual mode of the forklift. This
firmware uses original code from Craig Hennessey's own example firmware from our Introduction to Object Oriented Programming class from Term 3.  

# Theory of Operation
Once flashed, this firmware provides direct access to programmed pins and interfaces on the microcontroller. By sending commands over the serial port, we're able to read and write the states 
of devices attached to the pins of the microcontroller.  

The serial interface runs at a baud rate of 115200

## Commands
The commands are formatted using four arguments: the type of command, the kind of data being sent, the channel the data is associated with, and the actual data. For example:  

> ___S 1 0 255___  

Means "SET data of TYPE 1 (analog) on CHANNEL 0 to 255". This would effectively write a PWM signal of value 255 to the pin associated with channel 0.  
There are three kinds of possible commands: GET, SET, and ACK. ACK is reserved as a response to a GET command. For example, if a client over the serial port asks the microcontroller to get digital data from channel 3
> ___G 0 3___

The microcontroller might respond with something like:  

> ___A 0 3 1___

Which would mean that the microcontroller read a digital signal that was HIGH from channel 3.   

There are also three kinds of data that can be sent/requested: DIGITAL(0), ANALOG(1), and SERVO(2). These are differentiated from each other since each command takes different ranged values for the data. Digital signals only send/receive a 0 or 1, analog signals 0 to 255, and servo signals from 0 to 180. Commands expect that the following data argument is also formatted in the same way.

### Glossary of channels
Channels are not commutable, meaning that channel 0 in digital may not be channel 0 in analog. This allows us to keep devices on different pins from receiving signals that may be outside of what they're expecting. Below is a glossary of each channel available for each data type:

| # | Digital (0) | Analog (1) | Servo (2) |
|---|-------------|------------|-----------|
| 0 | SWITCH_S1   | JOYSTICK_X | SERVO_0   |
| 1 | SWITCH_S2   | JOYSTICK_Y |           |
| 2 | RGBLED_RED  | RGBLED_RED |           |
| 3 | RGBLED_GRN  | RGBLED_GRN |           |
| 4 | RGBLED_BLU  | RGBLED_BLU |           |
| 5 | SWITCH_J1   |            |           |
