# Client application
This folder contains the client application designed for our forklift system. It communicates with the server to control the movement of the forklift.  

This application also features tests that can be used to test the various systems of the forklift, including streaming the video from the onboard camera.
It also has simple ease-of-use features like last-configuration saving, debug settings, and clean server exiting.

## Usage
The client application is command line based. When launched, it checks to see if there are settings it can load, then proceeds to show a list of options.

<blockquote>
  
Select an option:   
(1) Connect to forklift server   
(2) Serial IO test   
(3) PI Video Stream test   
(4) UI test   
(5) Motor write test   
(6) Aruco nav test   
(0) Direct server command line   
   
(a) Save last connection parameters (with debug settings)   
(l) Load last settings   
(s) Settings   
(q) Quit   
>
</blockquote>

Apart from establishing a connection to the forklift, the client application provides multiple tests that allow you to evaluate the functionality of the robot's many features, all from the client computer.
