# ELEX 4699 Forklift

This repository is dedicated to the ELEX 4699 Forklift project for the four week term of May 2025. This project was designed, coded, and built by both me and [Rodriguez Chan](https://github.com/roddyguezchan). It is not intended for use by anyone else in the class as that is cheating and is a no-no, per BCIT :(   

If you are trying to read the server-specific README file, access it [here](SERVER_README.md)

If you are using this code for evaluation, note that all PIGPIO related code assumes that gpioInitialize() has been run prior to instantiation. For projects looking to use this code, make sure that gpioInitialize() has been run and that the program is being run with root privileges. The version of OpenCV used in this project requires a build with GStreamer support for reliable UDP streaming from the robot to the client program. Ensure that GStreamer is available upon compilation of OpenCV and that the binaries are available for use via the PATH environment variable in Windows.

## Objective
The goal of this project is to move "boxes" from one side of the playfield to the other side, sorted by Local and National (emulating a warehouse). The forklift starts in bottom left corner of the field (the start box) and navigates to the pickup area along the top part of the field. There, it picks up a box and moves it to the opposite end of the playfield. The box is supposed to be sorted in one of the corresponding shelves on the bottom part of the field depending on if it is local or national bound, based on its colour and ArUco tag. The robot sorts as many of the boxes as it can in 2.5 minutes, then navigates itself to the lower right corner of the field, designated as the finish box. The robot is meant to be able to navigate and sort both with remote control (manual operation), and completely by itself (autonomous), but the course does not dictate that both are required to pass the course. We are given two runs for evaluation, one of either mode, but passing the course is absolutely possible with one mode.

<img src=https://github.com/user-attachments/assets/a2d061b6-81b6-4d7a-adee-7e61a38bf6d3 width=250/>  

_Fig. 1 : Forklift playfield_

Our robot was designed with autonomous mode in mind, but due to some issues with our initial design, we did not have enough time to test and evaluate our code for the fully autonomous mode. The robot however, is fully functional in the manual mode, featuring both slow and fast mode controls, as well as a front facing camera to help with close-up navigation.

## Proof of concept
Below are some photos and videos of our project.  

<img src=https://github.com/user-attachments/assets/1db6be52-bf9e-416c-8b23-49311a1f8f62 width=300/>
<img src=https://github.com/user-attachments/assets/2dfbdf6d-9fd3-46f8-a8b2-93fbc71595f1 width=300/>

_Fig. 2 : Final design of our robot_

https://github.com/user-attachments/assets/2c703e52-625b-4b21-bedc-9972645ab3ba

_Fig. 3 : Final course evaluation run_  
(This video has been compressed to stay under 10MB)

## Theory of operation

### Server
The server is ran by a Raspberry PI 4, serving as the main controller of the forklift. It uses the PIGPIO library (https://abyz.me.uk/rpi/pigpio/) to facilitate the GPIO required to operate the servos and motors attached. The server communicates with a client over TCP/IP via some libraries created by Craig Hennessey, to receive the inputs used to drive and operate the forklift.

### Client
The client is ran by a separate computer, serving as the controls and brains of the forklift logic. The client program is responsible for reading the inputs from the TI BoosterPack (BOOSTXL-EDUMKII) using a TI Tiva Launchpad, which are used to control the forklift in manual operation. In automatic operation, it is responsible for deriving its position using an overhead camera available on the playfield, to determine where it needs to go to navigate and transit boxes around. For finer control, a front camera is used to determine how to pick up a box.

In short, the server (the forklift robot) acts like what is essentially a remote-control car with a forklift and a front camera. It provides an interface to the various onboard tools to the client, which sends commands over the network to control where the forklift goes and what to do with the fork. Both are needed to properly facilitate the forklift robot.

## Repository structure
The repository is structured such that the server is stored in the root, with the supplementary applications in their own separate subdirectories. Each program directory is organized with a /headers and /source directory to keep header and source files seperate. Programs are configured and built using the provided CMakeLists.txt in the directory pertaining to the program you wish to compile.
