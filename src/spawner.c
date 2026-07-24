#include "../include/runMethods.h"
#include <cjson/cJSON.h>
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
                    PlaySound(spawners[i].sound);
                }else
                {
                    PlaySound(spawners[i].sound);
                    UnloadTexture(spawners[i].texture);
                    UnloadSound(spawners[i].sound);
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
            if(spawners[i].lifetime<=spawners[i].warning)
            {
                DrawTexturePro(spawners[i].texture,spawners[i].scource,spawners[i].hurtbox,spawners[i].pos,0.0f,RED);
            }else{
                DrawTexturePro(spawners[i].texture,spawners[i].scource,spawners[i].hurtbox,spawners[i].pos,0.0f,WHITE);
            }
            DrawRectangle(spawners[i].hurtbox.x,spawners[i].hurtbox.y,spawners[i].hurtbox.width,spawners[i].hurtbox.height,BLANK);
            
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
                angle +=spawners.initalAngle*M_PI/180;
                bullets[j].velocx=cos(angle)*spawners.childVeloc;
                bullets[j].velocy=sin(angle)*spawners.childVeloc;
                bullets[j].texture=spawners.spawnTexture;
                bullets[j].hurtbox=spawners.hurtbox;
                bullets[j].pos=(Vector2){0,0};
                bullets[j].scource=(Rectangle){0,0,bullets[j].texture.width,bullets[j].texture.height};
                bullets[j].lifetime=spawners.childLifetime;
                bullets[j].damage=5;
                if(spawners.gravity)
                {
                    bullets[j].gravity=true;
                    bullets[j].gravStrength=spawners.gravStrength;
                    bullets[j].direction=spawners.direction;
                }
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
            beams[j].sound=spawners->sound;
            beams[j].angle=spawners->spread;
            beams[j].texture=spawners->spawnTexture;
            beams[j].fired=false;
            beams[j].scource=(Rectangle){0,0,beams[j].texture.width,beams[j].texture.height};
            beams[j].lifetime=spawners->childLifetime;
            beams[j].length=GAME_WIDTH;
            beams[j].maxPower=spawners->maxPower;
            beams[j].power=0;
            beams[j].hurtbox=(Rectangle){spawners->hurtbox.x,spawners->hurtbox.y,beams[j].length,0};
            beams[j].pos=(Vector2){0,beams[j].power/2};
            beams[j].decay=false;
            beams[j].damage=5;
            beams[j].decay_timer=30;
            *spawners=(struct spawner){0};
        }
    }
}

void spawnerSMaker(cJSON* move, struct fight *boss, int count)
{
    cJSON* textureJSON = cJSON_GetObjectItem(move,"texture");
    cJSON* childTextureJSON=cJSON_GetObjectItem(move, "childTexture");
    cJSON* posXJSON=cJSON_GetObjectItem(move,"pos_x");
    cJSON* posYJSON=cJSON_GetObjectItem(move,"pos_y");
    cJSON* velocXJSON=cJSON_GetObjectItem(move,"veloc_x");
    cJSON* velocyJSON=cJSON_GetObjectItem(move,"veloc_y");
    cJSON* widthJSON=cJSON_GetObjectItem(move,"width");
    cJSON* heightJSON=cJSON_GetObjectItem(move,"height");
    cJSON* damageJSON=cJSON_GetObjectItem(move,"damage");
    cJSON* behaviorJSON=cJSON_GetObjectItem(move, "behavior");
    cJSON* angleJSON=cJSON_GetObjectItem(move, "angle");
    cJSON* followJSON=cJSON_GetObjectItem(move,"follow");
    cJSON* repeatJSON=cJSON_GetObjectItem(move, "repeat");
    cJSON* repeat_delayJSON=cJSON_GetObjectItem(move, "repeat_delay");
    cJSON* lifetimeJSON=cJSON_GetObjectItem(move,"lifetime");
    cJSON* childLifetimeJSON=cJSON_GetObjectItem(move,"childLifetime");
    cJSON* delayJSON=cJSON_GetObjectItem(move,"delay");
    cJSON* maxPowerJSON=cJSON_GetObjectItem(move, "beamHeight");
    cJSON* warningJSON=cJSON_GetObjectItem(move, "warningDelay");
    cJSON* initalAngleJSON=cJSON_GetObjectItem(move, "initalAngle");
    cJSON* childVelocJSON=cJSON_GetObjectItem(move,"childVeloc");
    cJSON* soundJSON=cJSON_GetObjectItem(move, "sound");

    cJSON* gravityJSON=cJSON_GetObjectItem(move, "gravity");
    cJSON* gravity_DirectionJSON=cJSON_GetObjectItem(move, "gravity_direction");
    cJSON* gravity_strengthJSON=cJSON_GetObjectItem(move, "gravity_stength");
    char texture[250];
    char cTexture[250];
    char audio[250];
    sprintf(texture,"../images/%s",textureJSON->valuestring);
    sprintf(cTexture,"../images/%s",childTextureJSON->valuestring);
    sprintf(audio,"../sounds/%s",soundJSON->valuestring);
    for(int i=0;i<MAX_SPAWNERS;i++)
    {
        if(boss->attacks[count].moveset.spawnTimer[i]==0)
        {
            boss->attacks[count].moveset.spawners[i].texture=LoadTexture(texture);
            boss->attacks[count].moveset.spawners[i].spawnTexture=LoadTexture(cTexture);
            boss->attacks[count].moveset.spawners[i].sound=LoadSound(audio);
            boss->attacks[count].moveset.spawners[i].scource=(Rectangle){0,0,boss->attacks[count].moveset.spawners[i].texture.width,boss->attacks[count].moveset.spawners[i].texture.height};
            
            boss->attacks[count].moveset.spawners[i].hurtbox.x=posXJSON->valueint;
            boss->attacks[count].moveset.spawners[i].hurtbox.y=posYJSON->valueint;
            boss->attacks[count].moveset.spawners[i].hurtbox.width=GAME_WIDTH*widthJSON->valuedouble;
            boss->attacks[count].moveset.spawners[i].hurtbox.height=GAME_HEIGHT*heightJSON->valuedouble;
            
            boss->attacks[count].moveset.spawners[i].maxVecx=velocXJSON->valueint;
            boss->attacks[count].moveset.spawners[i].maxVecy=velocyJSON->valueint;

            boss->attacks[count].moveset.spawners[i].damage=damageJSON->valueint;
            boss->attacks[count].moveset.spawners[i].behaivor=behaviorJSON->valueint;
            boss->attacks[count].moveset.spawners[i].cont=repeatJSON->valueint;
            boss->attacks[count].moveset.spawners[i].contTime=repeat_delayJSON->valueint;
            boss->attacks[count].moveset.spawners[i].childLifetime=childLifetimeJSON->valueint;
            boss->attacks[count].moveset.spawners[i].fired=false;
            boss->attacks[count].moveset.spawners[i].spread=angleJSON->valueint;
            boss->attacks[count].moveset.spawners[i].initalAngle=initalAngleJSON->valueint;
            boss->attacks[count].moveset.spawners[i].warning=warningJSON->valueint;
            if(boss->attacks[count].moveset.spawners[i].behaivor==0)
            {
                boss->attacks[count].moveset.spawners[i].maxPower=maxPowerJSON->valueint;
            }else{
                boss->attacks[count].moveset.spawners[i].childVeloc=childVelocJSON->valueint;
            }

            boss->attacks[count].moveset.spawners[i].lifetime=lifetimeJSON->valueint;
            boss->attacks[count].moveset.spawnTimer[i]=delayJSON->valueint;

            switch(followJSON->valuestring[0])
            {
                case 'N':
                    boss->attacks[count].moveset.spawners[i].follow=false;
                    boss->attacks[count].moveset.spawners[i].velocx=boss->attacks[count].moveset.spawners[i].maxVecx;
                    boss->attacks[count].moveset.spawners[i].velocy=boss->attacks[count].moveset.spawners[i].maxVecy;
                    break;
                case'Y':
                    boss->attacks[count].moveset.spawners[i].follow=true;
            }
            if(gravityJSON!=NULL)
                {
                    char grav=gravityJSON->valuestring[0];
                    switch(grav)
                    {
                        case('Y'):
                            boss->attacks[count].moveset.spawners[i].gravity=true;
                            boss->attacks[count].moveset.spawners[i].gravStrength=gravity_strengthJSON->valuedouble;
                            char direc=gravity_DirectionJSON->valuestring[0];
                            switch(direc)
                            {
                                case 'L':
                                    boss->attacks[count].moveset.spawners[i].direction='L';
                                    break;
                                case'R':
                                    boss->attacks[count].moveset.spawners[i].direction='R';
                                    break;
                                case'U':
                                    boss->attacks[count].moveset.spawners[i].direction='U';
                                    break;
                                case'D':
                                    boss->attacks[count].moveset.spawners[i].direction='D';
                                    break;
                            }
                            break;
                        case('N'):
                            boss->attacks[count].moveset.spawners[i].gravity=false;

                    }
                }else{
                    boss->attacks[count].moveset.spawners[i].gravity=false;
                }


            boss->attacks[count].moveset.total++;
            break;
        }
        
    }
    
}

void spawnerSeqMaker(cJSON* move, struct fight *boss, int count)
{
    cJSON* textureJSON = cJSON_GetObjectItem(move,"texture");
    cJSON* childTextureJSON=cJSON_GetObjectItem(move, "childTexture");
    cJSON* posXJSON=cJSON_GetObjectItem(move,"pos_x");
    cJSON* posYJSON=cJSON_GetObjectItem(move,"pos_y");
    cJSON* velocXJSON=cJSON_GetObjectItem(move,"veloc_x");
    cJSON* velocyJSON=cJSON_GetObjectItem(move,"veloc_y");
    cJSON* widthJSON=cJSON_GetObjectItem(move,"width");
    cJSON* heightJSON=cJSON_GetObjectItem(move,"height");
    cJSON* damageJSON=cJSON_GetObjectItem(move,"damage");
    cJSON* behaviorJSON=cJSON_GetObjectItem(move, "behavior");
    cJSON* angleJSON=cJSON_GetObjectItem(move, "angle");
    cJSON* followJSON=cJSON_GetObjectItem(move,"follow");
    cJSON* repeatJSON=cJSON_GetObjectItem(move, "repeat");
    cJSON* repeat_delayJSON=cJSON_GetObjectItem(move, "repeat_delay");
    cJSON* lifetimeJSON=cJSON_GetObjectItem(move,"lifetime");
    cJSON* childLifetimeJSON=cJSON_GetObjectItem(move,"childLifetime");
    cJSON* delayJSON=cJSON_GetObjectItem(move,"delay");
    cJSON* maxPowerJSON=cJSON_GetObjectItem(move, "beamHeight");
    cJSON* countJSON=cJSON_GetObjectItem(move, "spawnerCount");
    cJSON* changeAngleJSON=cJSON_GetObjectItem(move, "changeAngle");
    cJSON* warningJSON=cJSON_GetObjectItem(move, "warningDelay");
    cJSON* initalAngleJSON=cJSON_GetObjectItem(move, "initalAngle");
    cJSON* childVelocJSON=cJSON_GetObjectItem(move,"childVeloc");
    cJSON* soundJSON=cJSON_GetObjectItem(move, "sound");

    cJSON* gravityJSON=cJSON_GetObjectItem(move, "gravity");
    cJSON* gravity_DirectionJSON=cJSON_GetObjectItem(move, "gravity_direction");
    cJSON* gravity_strengthJSON=cJSON_GetObjectItem(move, "gravity_stength");
    char texture[250];
    char cTexture[250];
    char audio[250];
    sprintf(texture,"../images/%s",textureJSON->valuestring);
    sprintf(cTexture,"../images/%s",childTextureJSON->valuestring);
    sprintf(audio,"../sounds/%s",soundJSON->valuestring);
    for(int z=0;z<countJSON->valueint;z++)
    {    
        for(int i=0;i<MAX_SPAWNERS;i++)
        {
            puts("beamMade");
            if(boss->attacks[count].moveset.spawnTimer[i]==0)
            {
                boss->attacks[count].moveset.spawners[i].texture=LoadTexture(texture);
                boss->attacks[count].moveset.spawners[i].spawnTexture=LoadTexture(cTexture);
                boss->attacks[count].moveset.spawners[i].sound=LoadSound(audio);
                boss->attacks[count].moveset.spawners[i].scource=(Rectangle){0,0,boss->attacks[count].moveset.spawners[i].texture.width,boss->attacks[count].moveset.spawners[i].texture.height};
            
                boss->attacks[count].moveset.spawners[i].hurtbox.x=posXJSON->valueint;
                boss->attacks[count].moveset.spawners[i].hurtbox.y=posYJSON->valueint;
                boss->attacks[count].moveset.spawners[i].hurtbox.width=GAME_WIDTH*widthJSON->valuedouble;
                boss->attacks[count].moveset.spawners[i].hurtbox.height=GAME_HEIGHT*heightJSON->valuedouble;
            
                boss->attacks[count].moveset.spawners[i].maxVecx=velocXJSON->valueint;
                boss->attacks[count].moveset.spawners[i].maxVecy=velocyJSON->valueint;

                boss->attacks[count].moveset.spawners[i].damage=damageJSON->valueint;
                boss->attacks[count].moveset.spawners[i].behaivor=behaviorJSON->valueint;
                boss->attacks[count].moveset.spawners[i].cont=repeatJSON->valueint;
                boss->attacks[count].moveset.spawners[i].contTime=repeat_delayJSON->valueint;
                boss->attacks[count].moveset.spawners[i].childLifetime=childLifetimeJSON->valueint;
                boss->attacks[count].moveset.spawners[i].fired=false;
                boss->attacks[count].moveset.spawners[i].spread=angleJSON->valueint+(z*changeAngleJSON->valueint);
                boss->attacks[count].moveset.spawners[i].initalAngle=initalAngleJSON->valueint;
                boss->attacks[count].moveset.spawners[i].warning=warningJSON->valueint;
                printf(" angle is %d",boss->attacks[count].moveset.spawners[i].spread);
                if(boss->attacks[count].moveset.spawners[i].behaivor==0)
                {
                    boss->attacks[count].moveset.spawners[i].maxPower=maxPowerJSON->valueint;
                }else{
                    boss->attacks[count].moveset.spawners[i].childVeloc=childVelocJSON->valueint;
                }

                boss->attacks[count].moveset.spawners[i].lifetime=lifetimeJSON->valueint;
                boss->attacks[count].moveset.spawnTimer[i]=delayJSON->valueint;

                switch(followJSON->valuestring[0])
                {
                    case 'N':
                        boss->attacks[count].moveset.spawners[i].follow=false;
                        boss->attacks[count].moveset.spawners[i].velocx=boss->attacks[count].moveset.spawners[i].maxVecx;
                        boss->attacks[count].moveset.spawners[i].velocy=boss->attacks[count].moveset.spawners[i].maxVecy;
                        break;
                    case'Y':
                        boss->attacks[count].moveset.spawners[i].follow=true;
                }
                if(gravityJSON!=NULL)
                {
                    char grav=gravityJSON->valuestring[0];
                    switch(grav)
                    {
                        case('Y'):
                            boss->attacks[count].moveset.spawners[i].gravity=true;
                            boss->attacks[count].moveset.spawners[i].gravStrength=gravity_strengthJSON->valuedouble;
                            char direc=gravity_DirectionJSON->valuestring[0];
                            switch(direc)
                            {
                                case 'L':
                                    boss->attacks[count].moveset.spawners[i].direction='L';
                                    break;
                                case'R':
                                    boss->attacks[count].moveset.spawners[i].direction='R';
                                    break;
                                case'U':
                                    boss->attacks[count].moveset.spawners[i].direction='U';
                                    break;
                                case'D':
                                    boss->attacks[count].moveset.spawners[i].direction='D';
                                    break;
                            }
                            break;
                        case('N'):
                            boss->attacks[count].moveset.spawners[i].gravity=false;

                    }
                }else{
                    boss->attacks[count].moveset.spawners[i].gravity=false;
                }
                boss->attacks[count].moveset.total++;
                break;
            }
        }
        
    }
}