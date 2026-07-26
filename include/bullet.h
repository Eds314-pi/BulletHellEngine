#pragma once
#include "3rdPartyIncludes.h"
#define MAX_BULLETS 1000
struct bullet
{
    Texture2D texture;
    Vector2 pos;
    Rectangle hurtbox;
    Rectangle scource;
    double maxVecx;
    double maxVecy;
    double velocx;
    double velocy;
    bool follow;
    bool gravity;
    //lifetimes are measured in frames 60fps is default
    int lifetime;    
    int damage;
    double gravStrength;
    char direction;
};