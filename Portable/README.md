### Portable Device
This project is designed to allow users to upload their content to a portable device to play on the go. This document will help with set up of portable device containing 3D models in this directory

## Components
1. Raspberry pi 4 with 2 GB of RAM or greater
2. waveshare 4 Inch Screen 800x480 Resolution for Raspberry pi 4B
3. PerfBoard
4. 5 mechanical buttons
5. 7 wires

## Wiring
- Solder all buttons onto the perfboard as shown on {INSERT PHOTO LOCATION} 
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
