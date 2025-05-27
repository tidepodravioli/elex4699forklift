# Server application
This application is meant to be run on the Raspberry PI as the main interface by which a client application can write and access the movement and data available on the forklift. It runs as the main application
on the PI, handling requests and performing the GPIO calls necessary to move the forklift around the playfield and the actual fork up and down.   

The server application does this by receiving commands over the network via TCP/IP. It then interprets these commands using a dictionary and performs the associated action or GPIO call. Commands are formatted
similarly to how the Tiva firmware commands are formatted (see [here](tiva/README.md)) with the exception that the data arguments are not strictly formatted. The channels are also different. 

## Channel glossary
Below is a glossary of all the available channels for writing to on the server. Next to each channel name is the expected input of the command. Note that some channels take two inputs, rather than just the one.

| #   | TOGGLE (0)    | ANALOG (1)                            | COMMAND (2)        |
|-----|---------------|---------------------------------------|--------------------|
| 0   | Fork up [1]   | Joystick drive [0 - 100, 0 - 100]     | Handshake          |
| 1   | Fork down [1] | Motor speeds [-255 - 255, -255 - 255] | Camera stream kill |
| 2   | Slow mode [1] | Forklift servo [0 - 180]              | Camera setup       |
| 10  |               | Drive distance in mm [-255 - 255]     |                    |
| 11  |               | Turn, in degrees [-180 - 180]         |                    |
| 12  |               | Turn, in radians [-π - π] × 1000      |                    |
| 110 |               | PID K_p [0.0+] × 1000                 |                    |
| 111 |               | PID K_i [0.0+] × 1000                 |                    |
| 112 |               | PID K_d [0.0+] × 1000                 |                    |

### Toggle channels
The toggle channels are channels that toggle flags (modes) on the server. They only require a 1 to be written to them to toggle or activate their state. If the state of the given channel is needed, it
can be read using the GET command.

## Analog channels
The analog channels allow the client to write directly to the server's interfaces.
