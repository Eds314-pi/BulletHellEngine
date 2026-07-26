#pragma once
#include "3rdPartyIncludes.h"

#define IMMUNITY_TIMER 90
struct player
    {
        bool immunity;
        bool gameOver;
        bool swap;

        Texture2D texture;
        Sound audio;
        Rectangle scource;
        Rectangle dest;
        Vector2 origin;
        Vector2 beamCollison[4];
        Color color;
        int time;
        int accelx;
        int accely;

        Rectangle currentHealth;
        Rectangle maxHealth;
        int health;
        int startHealth;
        
        bool freeMoveX;
        bool freeMoveY;
        int linex;
        int liney;
    };