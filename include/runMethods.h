#pragma once
#include "3rdPartyIncludes.h"
#include "bullet.h"
#include "Beam.h"
#include "Spawner.h"
#include "Player.h"
#include "Area.h"
#include "Background.h"
#include "Fight.h"




#define GAME_WIDTH 800
#define GAME_HEIGHT 600
void DrawBullets(struct bullet bullets[], Sound, Rectangle, bool*, int* health);
void updateBullets(struct bullet bullets[], Sound, Rectangle, bool*, int* health);
void updateBeams(struct beam beams[], Sound hurty, Sound beam, Vector2 beamCollison[4], bool* immunty, int* health);
void DrawBeams(struct beam beams[],Sound, Sound, Vector2[4], bool*, int* health);
void updateSpawner(struct spawner spawners[], struct beam beams[], struct bullet bullets[],Rectangle dest, Sound hurty,bool* immunity, int* health);
void DrawSpawner(struct spawner spawners[], struct beam beams[], struct bullet bullets[], Rectangle dest, bool* immunity, int* health);
   
    
    
   
   
    
void updateAttack(struct fight *fight, struct bullet *bullets, struct beam *beams, struct spawner *spawners);
void updateEvent(struct fight* boss, struct player *player, struct area *playableArea, struct background *background);
void updatePlayer(struct player*, struct area*);
void Drawplayer(struct player*);
void updateArea(struct player*, struct area*);
void DrawArea(struct area*);
void DrawBackground(struct background *background);
void setPlayerX(struct player *player, struct area *playablearea);
void setPlayerY(struct player *player, struct area *playablearea);
int gameplay(char* argv, bool*);