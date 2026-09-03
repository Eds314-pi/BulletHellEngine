### Configuring JSON
In order for the 'BulletHellEngine' to run a fight it must be in a JSON format explicitly given in this document. Attacks which consist of Bullets, Beams, and spawners are located within the
attacks category, while playable area, player, and death screen modifications are present within the event category. 'moves' and 'commands' are where attacks and events are stored, it is recommended
to create new move sets to ensure you can fit all attacks and for easier configuration. Xs are used to replace actual numbers which must be replaced

Use this as a skeleton to work in:
```json

{
  "name": "Example fight",
  "attackcount": 2,
  "attacks": [
    {
      "name": "Opening",
      "moveset": {
        "moves": [
          {
          }
        ]
        }
      }
  ],
  "event":[
  {
    "name":"startup",
    "commands":[
         {
         }
     ]
    }
  ]
}
```
## Bullet:
This creates one bullet in a specific spot
```json
"category": "B",
"type": "S",
"texture": "name.png",
"pos_x":-10,
"pos_y": 315,
"veloc_x": 4,
"veloc_y": 0,
"width": 0.02,
"height": 0.03,
"damage": 2,
"follow": "N",
"lifetime": 360,
"gravity":"N",
"gravity_direction":"L",
"gravity_stength":0.05,
"delay": 360
```
This creates x number of bullets in a spread
```json
"category": "B",
"type": "R",
"texture": "name.png",
"number": 200,
"pos_x": -100,
"seperation_x":100,
"pos_y": 600,
"seperation_y":100,
"veloc_x": 5,
"+-veloc_x":3,
"veloc_y": 0,
"+-veloc_y":0,
"width": 0.015,
"height": 0.02,
"damage": 2,
"gravity":"N",
"gravity_direction":"L",
"gravity_stength":0.05,
"delay": 1415,
"lifetime": 3000
```
NOTE: width and height are factors of screen height, follow and gravity are either Y or N, gravity direction is either "L","R","U" or "D" the if gravity is disabled 
neither gravity strength or direction is needed. Number is the number of bullets, +-[name] is the maximum variation

## Beam
This creates one beam in a specific spot 
```json
"category": "-",
"type": "S",
"texture": "name.png",
"pos_x": 0,
"seperation_x":0,
"pos_y": 525,
"seperation_y":-50,
"width": 3000,
"height": 50,
"damage": 5,
"angle": 0,
"change_angle":0,
"lifetime": 45,
"sound":"blaster.mp3",
"delay":295,
"beam_delay":45,
"decayDelay":5
```
This creates a line of beams 
```json
"category": "-",
"type": "L",
"texture": "name.png",
"number":5,
"pos_x": 0,
"seperation_x":0,
"pos_y": 525,
"seperation_y":-50,
"width": 3000,
"height": 50,
"damage": 5,
"angle": 0,
"change_angle":0,
"lifetime": 45,
"sound":"blaster.mp3",
"delay":295,
"beam_delay":45,
"decayDelay":5
```
Note: width and height are measured in pixels, angle starts facing to the right and moves clockwise, height is the maximum height as it grows to height, decayDelay is how many frames it has to 
shrink as the height decreases to 0, seperation is the amount of distance between beams in a line, change_angle changes the angle per beam, sound only works on Computer ports

## Spawners
Creates one spawner
```json
"category": "S",
"type" :"S",
"texture":"name.png",
"childTexture":"name.png",
"pos_x":350,
"pos_y":100,
"veloc_x":7,
"veloc_y":0,
"width":0.025,
"height":0.03,
"damage":2,
"behavior":8,
"angle":0,
"follow":"Y",
"repeat":7,
"repeat_delay":30,
"lifetime":60,
"childLifetime":2000,
"warningDelay":0,
"initalAngle":90,
"childVeloc":4,
"gravity":"N",
"gravity_direction":"R",
"gravity_stength":0.05,
"sound":"Pop.mp3",
"delay":100
```

Creates a stack of spawners in the same area
```json
"category": "S",
"type" :"E",
"texture":"name.png",
"childTexture":"name.png",
"pos_x":800,
"pos_y":350,
"veloc_x":-3,
"veloc_y":0,
"width":0.025,
"height":0.03,
"damage":5,
"behavior":0,
"angle":180,
"follow":"N",
"repeat":5,
"repeat_delay":30,
"lifetime":150,
"childLifetime":90,
"beamHeight":120,
"spawnerCount":4,
"changeAngle":90,
"warningDelay":30,
"gravity":"N",
"initalAngle":0,
"sound":"blaster.mp3",
"delay":900
```
Note: width and height are a percentage of screen size, damage is inherited by child, if behavior is greater than 0 the spawner will fire a x amount of bullets in a spread according to angle+inital angle. A spawner having repeat means after firing a bullet it will stay alive until repeat_delay is 0 then die (or repeat again), gravity does not affect spawner but its child 

## Area
Modifies playable area
```json
"category":"A",
"pos_x":200,
"pos_y":250,
"width":0.5,
"height":0.5,
"line_x":10,
"line_y":4,
"delay":0
```
Note: 'line' represents the amount of lines present on a grid system that can be enabled or disabled by modifying player directly, width and height are a percentage of screen size

## Player
Modifies player
```json
"category":"P",
"texture":"name.png",
"player_x":400,
"player_y":315,
"player_width":0.025,
"player_height":0.025,
"player_speedX":5,
"player_speedY":5,
"freeMoveX":"Y",
"freeMoveY":"N",
"sound":"hurt.mp3",
"health":10,
"delay":0
```
Note: freeMove is the enabling of a grid if N then a grid using line in area is made and the player is locked onto them, sound is the hurt sound that plays whenever a player is hurt, width and height are a percentage of screen height. Only "texture", "freeMoveX","freeMoveY", and "delay" are required for this method

## Death Screen
Creates the Death Screen
```json
"category":"D",
"texture":"Gray.png",
"text":"You are Dead",
"shade":"#8f001d",
"pos_x":300,
"pos_y":200,
"size":32
```
Note: Texture is automatically size of screen only text is modified by shade position and size, shade is in hexadecimal
