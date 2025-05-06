# ELEX 4699 Forklift

This repository is dedicated to the ELEX 4699 Forklift project for the four week term. It is not intended for use by anyone else in the class as that is cheating and is a no-no, per BCIT :(

*I see you, Derek Wilson...* :(

All PIGPIO related code assumes that gpioInitialize() has been run prior to instantiation. For projects looking to use this code, make sure that gpioInitialize() has been run and that the program is being run with root privileges.

  

## Theory of operation
### Server
The server is ran by a Raspberry PI 4, serving as the brains of the forklift. It uses the PIGPIO library (https://abyz.me.uk/rpi/pigpio/) to facilitate the GPIO required to operate the servos and motors attached. The server communicates with a client over TCP/IP via some libraries created by Craig Hennessey, to receive the inputs used to drive and operate the forklift.

### Client
The client is ran by a separate computer, serving as the controls of the forklift. The client program is responsible for reading the inputs from the TI BoosterPack (BOOSTXL-EDUMKII) using a TI Tiva Launchpad, which are used to control the forklift in manual operation. In automatic operation, it is responsible for deriving its position using an overhead camera available on the playfield, to determine where it needs to go to navigate and transit boxes around. For finer control, a front camera is used to determine how to pick up a box.