#include "../include/runMethods.h"
void spawnBullet(struct spawner spawners, struct bullet bullets[]);
void spawnBeam(struct spawner *spawners, struct beam beams[]);

void updateSpawner(struct spawner spawners[], struct beam beams[], struct bullet bullets[], Rectangle dest, Sound hurty,bool* immunity, int* health)
{
    for(int i=0;i<MAX_SPAWNERS;i++)
    {
        if(spawners[i].lifetime!=0)
        {
            spawners[i].lifetime--;
            if(spawners[i].follow)
            {
                spawners[i].velocx=spawners[i].maxVecx*cos(atan2(dest.y-spawners[i].hurtbox.y,dest.x-spawners[i].hurtbox.x));
                spawners[i].velocy=spawners[i].maxVecy*sin(atan2(dest.y-spawners[i].hurtbox.y,dest.x-spawners[i].hurtbox.x));
            }
            spawners[i].hurtbox.x+=spawners[i].velocx;
            spawners[i].hurtbox.y+=spawners[i].velocy;
            if(CheckCollisionRecs(dest,spawners[i].hurtbox) && !(*immunity))
            {
                spawners[i].lifetime=0;
                spawners[i].cont=0;
                spawners[i].fired=true;
                *health-=spawners[i].damage;
                PlaySound(hurty);
                *immunity=true;
                
            }
        }else
            {
            if(spawners[i].behaivor>0 && !spawners[i].fired)
            {
                spawnBullet(spawners[i],bullets);
                //Resets timer for the spawner to shoot multiple times
                if(spawners[i].cont>0)
                {
                    spawners[i].lifetime=spawners[i].contTime;
                    spawners[i].cont--;
                    PlaySound(spawners[i].pop);
                }else
                {
                    //spawners[i].fired=true;
                    spawners[i]=(struct spawner){0};
                }
                
            }else if(!spawners[i].fired)
            {
                spawnBeam(&spawners[i],beams);
            }
        }
    }
}
void DrawSpawner(struct spawner spawners[], struct beam beams[], struct bullet bullets[], Rectangle dest,bool* immunity,int* health)
{
    for(int i=0;i<MAX_SPAWNERS;i++)
    {
        if(spawners[i].lifetime!=0)
        {
            DrawRectangle(spawners[i].hurtbox.x,spawners[i].hurtbox.y,spawners[i].hurtbox.width,spawners[i].hurtbox.height,BLANK);
            DrawTexturePro(spawners[i].texture,spawners[i].scource,spawners[i].hurtbox,spawners[i].pos,0.0f,WHITE);
        }
    }
}
void spawnBullet(struct spawner spawners, struct bullet bullets[])
{
    for(int l=0;l<spawners.behaivor;l++)
    {
        for(int j=0;j<MAX_BULLETS;j++)
        {
            if(bullets[j].lifetime==0)
            {
                double angle=l*( (spawners.spread*M_PI/180) /spawners.behaivor);
                bullets[j].velocx=cos(angle)*10;
                bullets[j].velocy=sin(angle)*10;
                bullets[j].texture=spawners.spawnTexture;
                bullets[j].hurtbox=spawners.hurtbox;
                bullets[j].pos=(Vector2){0,0};
                bullets[j].scource=(Rectangle){0,0,bullets[j].texture.width,bullets[j].texture.height};
                bullets[j].lifetime=spawners.childLifetime;
                bullets[j].damage=5;
                break;
            }
        }
    }
}
void spawnBeam(struct spawner *spawners, struct beam beams[])
{
    for(int j=0;j<MAX_BEAMS;j++)
    {
        if(beams[j].lifetime==0)
        {
            beams[j].angle=spawners->spread;
            beams[j].texture=spawners->spawnTexture;
            beams[j].fired=false;
            beams[j].scource=(Rectangle){0,0,beams[j].texture.width,beams[j].texture.height};
            beams[j].lifetime=spawners->childLifetime;
            beams[j].length=GetScreenWidth();
            beams[j].maxPower=spawners->maxPower;
            beams[j].power=0;
            beams[j].hurtbox=(Rectangle){spawners->hurtbox.x,spawners->hurtbox.y,beams[j].length,0};
            beams[j].pos=(Vector2){0,beams[j].power/2};
            beams[j].decay=false;
            beams[j].damage=5;
            *spawners=(struct spawner){0};
        }
    }
}