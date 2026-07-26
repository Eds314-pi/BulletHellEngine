#pragma once
#include "3rdPartyIncludes.h"

#define MAX_SPAWNERS 100
struct spawner
    {
        Texture2D texture;
        Texture2D spawnTexture;
        Sound sound;
        Vector2 pos;
        Rectangle hurtbox;
        Rectangle scource;
        Sound pop;
        double maxVecx;
        double maxVecy;
        double velocx;
        double velocy;
        //lifetimes are measured in frames 60fps is default
        int lifetime;
        int childLifetime;
        int spread;
        int initalAngle;
        int behaivor;
        int maxPower;
        int cont;
        int contTime;
        int damage;
        int warning;
        int childVeloc;
        bool follow;
        bool fired;
        bool gravity;
        double gravStrength;
        char direction;
        
    };