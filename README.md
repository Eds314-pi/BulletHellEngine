<img width="1152" height="720" alt="ComputerDemo" src="https://github.com/user-attachments/assets/1eb86371-1e63-4665-8631-ddb48b1b5b4d" />


# BulletHellEngine
## Premise
This project is an engine for the bullet hell archetype of games. Using the software version built for a computer a user can create their own custom fights and transfer them to then play their own content on the portable device. The goal is for the user to have the freedom to use their full creativity to build encounters and patterns to their own liking without needing to code an entire game around it. 


## Features
Easy to use "events" and "attacks" commands for users to customize their content using a configured JSON.
Ability to chain together "attacks" and "events" in tandem for more in-depth experience.
High customization on bullets, beams, spawners, player, area for full creative control.
Optimized engine able to handle 300+ bullets on the Raspberry Pi 4.

## Getting Started

### Computer Requirements
1. Raylib
2. cJSON


### Portable Requirements
1. Raylib
2. cJSON
3. Raspberry Pi 4
4. Raspberry Pi Os
5. Waveshare 4-inch Screen
6. 5 Buttons

### Installation 
Clone the repository (No additional steps required)
Ensure all textures, sounds, and JSON files are located within their respective folders within repository 

### Running 
Compile the program in the terminal using "gcc *.c -lcjson -o game -lraylib -lm -lpthread -ldl -lrt -lX11" in 'src' directory 

Controls:
Up/Down: Select desired JSON file
Right: Begin Fight
Arrow Keys: Move player
Tab: Return to main menu

