

### Portable Device
This project is designed to allow users to upload their content to a portable device to play on the go. This document will help with set up of portable device containing 3D models in this directory

## Components
- Raspberry pi 4 with 2 GB of RAM or greater
-  waveshare 4 Inch Screen 800x480 Resolution for Raspberry pi 4B
-  PerfBoard



-  5 mechanical buttons
-  7 wires

## Wiring
- Solder all buttons onto the perfboard as shown on Portable Setup.png
- Solder wires to buttons maintaining a diagonal between pins (It is recommended to have a common ground between arrow keys) 
- Connect GPIO BCM pins to wires: 
- 26 to up button 
- 13 to left button 
- 6 to Right button 
- 5 to Down Button 
- 12 to Return/Tab

## Software
- Install Raspberry pi OS 64-bit
- Attach waveshare monitor and power on device
- Download main branch of git repository
- Install Raylib 
- Install OpenGL (configure to ver. 2.1 as Raspberry pi 4 automatically install most up to date)
- Set monitor to be x11 in Advanced options
- Set up Raspberry pi to run project on startup

## Assembly
- Secure perfboard using screws to 'base' 
- Secure Raspberry pi using bolts and nuts to 'base' 
- Drill holes for your buttons through 'cover' 
- Attach and secure 'cover' to 'base' using screws

## Boot up Video
https://drive.google.com/file/d/1X7fE6cZNJxw-XGoSLpnj0Yf7Wo-p8V3L/view?usp=sharing
