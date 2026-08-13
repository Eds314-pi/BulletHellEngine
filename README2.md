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
This creates one bullet in a specific spot according to customization 
```json
"category": "B",
"type": "S",
"texture": "name.png",
"pos_x":x,
"pos_y": x,
"veloc_x": x,
"veloc_y": x,
"width": x.x, 
"height": x.x,
"damage": x,
"follow": "N",
"lifetime": x,
"gravity":"N",
"gravity_direction":"L"
"gravity_stength":x
"delay": x
```
This creates x number of bullets in a spread according to customization
```json
"category": "B",
"type": "R",
"texture": "name.png",
"number": x,
"pos_x": x,
"seperation_x":x,
"pos_y": x,
"seperation_y":x,
"veloc_x": x,
"+-veloc_x":x,
"veloc_y": x,
"+-veloc_y":x,
"width": x.x,
"height": x.x,
"damage": x,
"follow": "N",
"lifetime": x,
"gravity":"N",
"gravity_direction":"L"
"gravity_stength":x
"delay": x
```
NOTE: width and height are factors of screen height, follow and gravity are either Y or N, gravity direction is either "L","R","U" or "D" the if gravity is disabled 
neither gravity strength or direction is needed. Number is the number of bullets, +-[name] is the maximum variation

## Beam
This creates one beam in a specific spot according to customization 
"category": "-",
"type": "S",
"texture": "name.png",
"number":x,
"pos_x": x,
"pos_y": x,
"width": x,
"height": x,
"damage": x,
"angle": x,
"lifetime": x,
"sound":"name.mp3",
"delay":x,
"decayDelay":x

This creates a line of beams according to customization 
"category": "-",
"type": "L",
"texture": "Beam.png",
"number":3,
"pos_x": 2200,
"seperation_x":-400,
"pos_y": 0,
"seperation_y":0,
"width": 3000,
"height": 200,
"damage": 5,
"angle": 90,
"change_angle":0,
"lifetime": 45,
"sound":"blaster.mp3",
"delay":460,
"beam_delay":45,
"decayDelay":5

Note: width and height are measured in pixels, angle starts facing to the right and moves clockwise, height is the maximum height as it grows to height, decayDelay is how many frames it has to 
shrink as the height decreases to 0, seperation is the amount of distance between beams in a line, change_angle changes the angle per beam, sound only works on Computer ports

## Spawners
Creates one spawner

"category": "S",
"type" :"S",
"texture":"name.png",
"childTexture":"name.png",
"pos_x":x,
"pos_y":x,
"veloc_x"x,
"veloc_y":x,
"width":x.x,
"height":x.x,
"damage":x,
"behavior":x,
"angle":x,
"follow":"N",
"repeat":x,
"repeat_delay":x,
"lifetime":x,
"childLifetime":x,
"warningDelay":x,
"initalAngle":x,
"childVeloc":x,
"gravity":"Y",
"gravity_direction":"R",
"gravity_stength":x.x,
"sound":"name.mp3",
"delay":x


Creates a stack of spawners in the same area
"category": "S",
"type" :"E",
"texture":"name.png",
"childTexture":"name.png",
"pos_x":x,
"pos_y":x,
"veloc_x":x,
"veloc_y":x,
"width":x.x,
"height":x.x,
"damage":x,
"behavior":x,
"angle":x,
"follow":"N",
"repeat":x,
"repeat_delay":x,
"lifetime":x,
"childLifetime":x,
"beamHeight":x,
"spawnerCount":x,
"changeAngle":x,
"warningDelay":x,
"gravity":"N",
"initalAngle":x,
"sound":"name.mp3",
"delay":x

Note: width and height are a percentage of screen size, damage is inherited by child, if behavior is greater than 0 the spawner will fire a x amount of bullets in a spread according to angle+inital angle. A spawner having repeat means after firing a bullet it will stay alive until repeat_delay is 0 then die (or repeat again), gravity does not affect spawner but its child 

## Area
Modifies playable area
"category":"A",
"pos_x":x,
"pos_y":x,
"width":x.x,
"height":x.x,
"line_x":x,
"line_y":x,
"delay":x

Note: 'line' represents the amount of lines present on a grid system that can be enabled or disabled by modifying player directly, width and height are a percentage of screen size

## Player
Modifies player
"category":"P",
"texture":"name.png",
"player_x":x,
"player_y":x,
"player_width":x.x,
"player_height":x.x,
"player_speedX":x,
"player_speedY":x,
"freeMoveX":"Y",
"freeMoveY":"Y",
"sound":"name.mp3",
"health":x,
"delay":x

Note: freeMove is the enabling of a grid if N then a grid using line in area is made and the player is locked onto them, sound is the hurt sound that plays whenever a player is hurt, width and height are a percentage of screen height. Only "texture", "freeMoveX","freeMoveY", and "delay" are required for this method

## Death Screen
Creates the Death Screen
"category":"D",
"texture":"Gray.png",
"text":"You are Dead",
"shade":"#8f001d",
"pos_x":500,
"pos_y":500,
"size":32

Note: Texture is automatically size of screen only text is modified by shade position and size, shade is in hexadecimal
