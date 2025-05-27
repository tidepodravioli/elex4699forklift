# Server application
This application is meant to be run on the Raspberry PI as the main interface by which a client application can write and access the movement and data available on the forklift. It runs as the main application
on the PI, handling requests and performing the GPIO calls necessary to move the forklift around the playfield and the actual fork up and down.   

The server application does this by receiving commands over the network via TCP/IP. It then interprets these commands using a dictionary and performs the associated action or GPIO call. Commands are formatted
similarly to how the Tiva firmware commands are formatted (see [here](tiva/README.md)) with the exception that the data arguments are not strictly formatted. The channels are also different. 

## Channel glossary
Below is a glossary of all the available channels for writing to on the server. Next to each channel name is the expected input of the command. Note that some channels take two inputs, rather than just the one.

| #   | TOGGLE (0)                      | ANALOG (1)                                                      | COMMAND (2)                                   |
|-----|---------------------------------|-----------------------------------------------------------------|-----------------------------------------------|
| 0   | [Fork up](#0---fork-up) [1]     | [Joystick drive](#0---joystick-drive) [0 - 100, 0 - 100]        | [Handshake](#0---handshake)                   |
| 1   | [Fork down](#1---fork-down) [1] | [Motor speeds](#1---motor-speeds) [-255 - 255, -255 - 255]      | [Camera stream kill](#1---camera-stream-kill) |
| 2   | [Slow mode](#2---slow-mode) [1] | [Forklift servo](#2---forklift-servo) [0 - 180]                 | [Camera setup](#2---camera-setup)             |
| 10  |                                 | [Drive distance](#10---drive-distance-in-mm) in mm [-255 - 255] |                                               |
| 11  |                                 | [Turn, in degrees](#11---turn-in-degrees) [-180 - 180]          |                                               |
| 12  |                                 | [Turn, in radians](#12---turn-in-radians) [-π - π] × 1000       |                                               |
| 110 |                                 | [PID K_p](#110---pid-k_p) [0.0+] × 1000                         |                                               |
| 111 |                                 | [PID K_i](#111---pid_k_i) [0.0+] × 1000                         |                                               |
| 112 |                                 | [PID K_d](#112---pid-k_d) [0.0+] × 1000                         |                                               |

### Toggle channels
The toggle channels are channels that toggle flags (modes) on the server. They only require a 1 to be written to them to toggle or activate their state. If the state of the given channel is needed, it
can be read using the GET command.

#### 0 - Fork up
Moves the fork up one preset level

#### 1 - Fork down
Moves the fork down one preset level

#### 2 - Slow mode
Toggles the slow mode, which limits the maximum speed that is written via PWM

### Analog channels
The analog channels allow the client to write directly to the server's interfaces. 

#### 0 - Joystick drive
This channel allows the client to write scaled joystick input to the server. The class [RMotorDriver](headers/RMotorDriver.hpp) (or if with feedback, [RMotorDriverF](headers/RMotorDriverF.hpp) ) provides a method that translates this scaled input to the required PWM values for the motor for more natural driving.

#### 1 - Motor speeds
Directly writes to the motor's GPIO using PWM

#### 2 - Forklift servo
Directly writes to the servo controlling the forklift (in degrees)

#### 10 - Drive distance in mm
Drives straight for a given distance. Only possible with the encoded motors.

#### 11 - Turn, in degrees
Turns the robot in place with the given angular displacement (in degrees)

#### 12 - Turn, in radians
Turns the robot in place with the given angular displacement (in radians × 1000)

#### 110 - PID K_p
Sets the robot's PID K_p coefficient on the fly for debugging. (× 1000)

#### 111 - PID K_i
Sets the robot's PID K_i coefficient on the fly for debugging. (× 1000)

#### 112 - PID K_d
Sets the robot's PID K_d coefficient on the fly for debugging. (× 1000)

### Command channels
The command channels are reserved for configuration of services that aren't strictly GPIO related.

#### 0 - Handshake
This command sends the same values back, but as an ACK. This allows the server and client to confirm that communication is working.

#### 1 - Camera stream kill
Ideally, only one camera stream should be happening as multiple streams have the potential of throttling the CPU on the PI. Sending this command will kill the last established stream.

#### 2 - Camera setup
This command establishes a GStreamer UDP stream on the given port.


