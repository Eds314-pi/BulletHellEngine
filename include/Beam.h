#pragma once
#include "3rdPartyIncludes.h"

#define MAX_BEAMS 100
#define DECAY_TIMER 15
struct beam
{   
    Texture2D texture;
    Sound sound;
    Rectangle scource;
    Vector2 pos;
    Vector2 collison[4];
    Rectangle hurtbox;
    int width;;
    int length;
    //lifetimes are measured in frames 60fps is default
    int lifetime;
    //Clockwise startin at 0 (horizontal) going to 359
    float angle;
    int power;
    int maxPower;
    int delay;
    int damage;
    int decay_timer;
    bool fired;
    bool decay;
};