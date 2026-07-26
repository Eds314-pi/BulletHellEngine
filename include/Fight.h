#pragma once
#include "3rdPartyIncludes.h"
#include "runMethods.h"

#define MAX_ATTACKS 50
#define MAX_MOVES 100
#define MAX_EVENTS 50

struct moves
{
    struct bullet bullets[MAX_BULLETS];
    struct beam beams[MAX_BEAMS];
    struct spawner spawners[MAX_SPAWNERS];
    int bulletTimer[MAX_BULLETS];
    int beamTimer[MAX_BEAMS];
    int spawnTimer[MAX_SPAWNERS];
    int total;
};
struct attack
{
    struct moves moveset;
};

struct commands
{
    struct player playa;
    struct area plyablearea;
    struct background background;
    int timer;
    int id;
};
struct event
{
    struct commands orders;
};

struct fight
{
    struct attack attacks[MAX_ATTACKS];
    struct event events[MAX_EVENTS];
    int currentAttack;
    int currentEvent;
    bool finished;
};

//Fight is the top layer which contains attacks and events
//attacks contain moves which contain the actual attack pattern
//events contain commands which contain the actual changes to constant objects 