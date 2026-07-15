#pragma once
#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include <cjson/cJSON.h>

#define MAX_BULLETS 1000
#define MAX_BEAMS 100
#define MAX_SPAWNERS 100
#define IMMUNITY_TIMER 90
#define DECAY_TIMER 15
#define MAX_LINEX 100
#define MAX_LINEY 100
#define MAX_ATTACKS 10
#define MAX_MOVES 100


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
        //lifetimes are measured in frames 60fps is default
        int lifetime;    
        int damage;
    };
    void DrawBullets(struct bullet bullets[], Sound, Rectangle, bool*, int* health);
    void updateBullets(struct bullet bullets[], Sound, Rectangle, bool*, int* health);
    struct beam
    {   
        Texture2D texture;
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
        int damage;
        bool fired;
        bool decay;
    };
    void updateBeams(struct beam beams[], Sound hurty, Sound beam, Vector2 beamCollison[4], bool* immunty, int* health);
    void DrawBeams(struct beam beams[],Sound, Sound, Vector2[4], bool*, int* health);
    struct spawner
    {
        Texture2D texture;
        Texture2D spawnTexture;
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
        int behaivor;
        int maxPower;
        int cont;
        int contTime;
        int damage;
        bool follow;
        bool fired;
        
    };
    void updateSpawner(struct spawner spawners[], struct beam beams[], struct bullet bullets[],Rectangle dest, Sound hurty,bool* immunity, int* health);
    void DrawSpawner(struct spawner spawners[], struct beam beams[], struct bullet bullets[], Rectangle dest, bool* immunity, int* health);
   
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
    struct fight
    {
        struct attack attacks[MAX_ATTACKS];
        int currentAttack;
    };
    void updateAttack(struct fight *fight, struct bullet *bullets);
    struct player
    {
        bool immunity;
        bool gameOver;
        bool swap;

        Texture2D texture;
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
    struct area
    {
        
        Rectangle playable;
        int lockx[MAX_LINEX];
        int locky[MAX_LINEY];
        int linex;
        int liney;

    };
    void updatePlayer(struct player*, struct area*);
    void Drawplayer(struct player*);
    void updateArea(struct player*, struct area*);
    void DrawArea(struct area*);
