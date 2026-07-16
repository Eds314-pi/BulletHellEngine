#include "../include/runMethods.h"
#include <cjson/cJSON.h>
//Decay activates whenever decay timer is the only frames left is slowly dissapate beam 
void growthDecay(struct beam*beams, Sound hurty, Sound beam, Vector2 beamCollison[],bool* immunity, int* health);
void updateBeams(struct beam beams[], Sound hurty, Sound beam, Vector2 beamCollison[], bool* immunty, int* health)
{
    for(int i=0;i<MAX_BEAMS;i++)
    {
        if(beams[i].delay==0)
        {
            if(beams[i].lifetime!=0)
            {
                growthDecay(&beams[i], hurty, beam, beamCollison, immunty, health);
                Vector2 origin = {beams[i].hurtbox.x + beams[i].pos.x,beams[i].hurtbox.y + beams[i].pos.y};
                beams[i].pos = (Vector2){0, beams[i].hurtbox.height / 2};
                float a = beams[i].angle * DEG2RAD;


                Vector2 corners[4];
                corners[0] = (Vector2){beams[i].hurtbox.x, beams[i].hurtbox.y};
                corners[1] = (Vector2){beams[i].hurtbox.x + beams[i].hurtbox.width, beams[i].hurtbox.y};
                corners[2] = (Vector2){beams[i].hurtbox.x + beams[i].hurtbox.width, beams[i].hurtbox.y + beams[i].hurtbox.height};
                corners[3] = (Vector2){beams[i].hurtbox.x, beams[i].hurtbox.y + beams[i].hurtbox.height};

                for(int j = 0; j < 4; j++)
                {
                    float x = corners[j].x - origin.x;
                    float y = corners[j].y - origin.y;
                    beams[i].collison[j].x = origin.x + x*cosf(a) - y*sinf(a);
                    beams[i].collison[j].y = origin.y + x*sinf(a) + y*cosf(a);
                }
                beams[i].lifetime--;
                if(beams[i].lifetime==0)
                {
                    beams[i]=(struct beam){0};
                }
            }
        }else{
            beams[i].delay--;
        }
    }
}

void DrawBeams(struct beam beams[], Sound hurty, Sound beam, Vector2 beamCollison[], bool* immunty, int* health)
{
    for(int i=0;i<MAX_BEAMS;i++)
    {
        if(beams[i].lifetime!=0)
        {
            DrawTexturePro(beams[i].texture,beams[i].scource,beams[i].hurtbox,beams[i].pos,beams[i].angle,WHITE);
        }
    }
}

void growthDecay(struct beam*beams, Sound hurty, Sound beam, Vector2 beamCollison[],bool* immunity, int* health)
{
    if(beams->lifetime==DECAY_TIMER)
    {
        beams->decay=true;
    }
    //ensures sound playes once
    if(!beams->fired)
    {
        PlaySound(beam);
        beams->fired=true;
    }
    if(beams->power<beams->maxPower && !beams->decay)
            {
                beams->power += (float)beams->maxPower / 30.0f;
                beams->hurtbox.height=beams->power;
            }else 
                //Only checks for collision assuming beam is at full power
                for(int j=0;j<4;j++)
                {
                    if(CheckCollisionPointPoly((Vector2){beamCollison[j].x,beamCollison[j].y},beams->collison,4) && !beams->decay)
                    {
                        if(!(*immunity))
                        {
                            *health-=beams->damage;
                            *immunity=true;
                            PlaySound(hurty);
                            printf("collison with beam %d",j);
                        }
                    }
                }

            if(beams->decay)
            {
                beams->power -= (float)beams->maxPower / 30.0f;
                beams->hurtbox.height=beams->power;
            }
}

void beamSMaker(cJSON *move, struct fight *boss, int count)
{
    cJSON* textureJSON=cJSON_GetObjectItem(move,"texture");
    cJSON* pos_xJSON=cJSON_GetObjectItem(move,"pos_x");
    cJSON* pos_yJSON=cJSON_GetObjectItem(move,"pos_y");
    cJSON* widthJSON=cJSON_GetObjectItem(move,"width");
    cJSON* maxPowerJSON=cJSON_GetObjectItem(move,"height");
    cJSON* damageJSON=cJSON_GetObjectItem(move,"damage");
    cJSON* angleJSON=cJSON_GetObjectItem(move,"angle");
    cJSON* lifetimeJSON=cJSON_GetObjectItem(move,"lifetime");
    cJSON* delayJSON=cJSON_GetObjectItem(move, "delay");
    char texture[250];
    sprintf(texture,"../images/%s",textureJSON->valuestring);

    for(int i=0;i<MAX_BEAMS;i++)
    {
        if(boss->attacks[count].moveset.beams[i].lifetime==0)
        {
            boss->attacks[count].moveset.beams[i].texture=LoadTexture(texture);
            boss->attacks[count].moveset.beams[i].hurtbox.x=pos_xJSON->valueint;
            boss->attacks[count].moveset.beams[i].hurtbox.y=pos_yJSON->valueint;
            boss->attacks[count].moveset.beams[i].hurtbox.width=widthJSON->valueint;
            boss->attacks[count].moveset.beams[i].hurtbox.height=0;
            //height is set through power of beam during start up and end of firing
            boss->attacks[count].moveset.beams[i].maxPower=maxPowerJSON->valueint;
            boss->attacks[count].moveset.beams[i].damage=damageJSON->valueint;
            boss->attacks[count].moveset.beams[i].angle=angleJSON->valueint;
            boss->attacks[count].moveset.beams[i].lifetime=lifetimeJSON->valueint;
            boss->attacks[count].moveset.beamTimer[i]=delayJSON->valueint;
            
            boss->attacks[count].moveset.beams[i].scource=(Rectangle){0,0,boss->attacks[count].moveset.beams[i].texture.width,boss->attacks[count].moveset.beams[i].texture.height};
            boss->attacks[count].moveset.beams[i].pos=(Vector2){boss->attacks[count].moveset.beams[i].hurtbox.x,boss->attacks[count].moveset.beams[i].hurtbox.y};
            boss->attacks[count].moveset.beams[i].delay=0;
            boss->attacks[count].moveset.total++;
            break;
        }
    }
}

void beamLMaker(cJSON* move, struct fight *boss, int count)
{
    cJSON* textureJSON=cJSON_GetObjectItem(move,"texture");
    cJSON* pos_xJSON=cJSON_GetObjectItem(move,"pos_x");
    cJSON* pos_yJSON=cJSON_GetObjectItem(move,"pos_y");
    cJSON* widthJSON=cJSON_GetObjectItem(move,"width");
    cJSON* maxPowerJSON=cJSON_GetObjectItem(move,"height");
    cJSON* damageJSON=cJSON_GetObjectItem(move,"damage");
    cJSON* angleJSON=cJSON_GetObjectItem(move,"angle");
    cJSON* lifetimeJSON=cJSON_GetObjectItem(move,"lifetime");
    cJSON* delayJSON=cJSON_GetObjectItem(move, "delay");
    cJSON* numberJSON=cJSON_GetObjectItem(move, "number");
    cJSON* seperation_xJSON=cJSON_GetObjectItem(move,"seperation_x");
    cJSON* seperation_yJSON=cJSON_GetObjectItem(move,"seperation_y");
    cJSON* change_angleJSON=cJSON_GetObjectItem(move,"change_angle");
    cJSON* beamtimeJSON=cJSON_GetObjectItem(move,"beam_delay");
    char texture[250];
    sprintf(texture,"../images/%s",textureJSON->valuestring);

    for(int z=0;z<numberJSON->valueint;z++)
    {
        for(int i=0;i<MAX_BEAMS;i++)
        {
            if(boss->attacks[count].moveset.beams[i].lifetime==0)
            {
                boss->attacks[count].moveset.beams[i].texture=LoadTexture(texture);
                boss->attacks[count].moveset.beams[i].hurtbox.x=pos_xJSON->valueint+seperation_xJSON->valueint*z;
                boss->attacks[count].moveset.beams[i].hurtbox.y=pos_yJSON->valueint+seperation_yJSON->valueint*z;
                boss->attacks[count].moveset.beams[i].hurtbox.width=widthJSON->valueint;
                boss->attacks[count].moveset.beams[i].hurtbox.height=0;
                //height is set through power of beam during start up and end of firing
                boss->attacks[count].moveset.beams[i].maxPower=maxPowerJSON->valueint;
                boss->attacks[count].moveset.beams[i].damage=damageJSON->valueint;
                boss->attacks[count].moveset.beams[i].angle=angleJSON->valueint+change_angleJSON->valueint*z;
                boss->attacks[count].moveset.beams[i].lifetime=lifetimeJSON->valueint;
                boss->attacks[count].moveset.beamTimer[i]=delayJSON->valueint;
            
                boss->attacks[count].moveset.beams[i].scource=(Rectangle){0,0,boss->attacks[count].moveset.beams[i].texture.width,boss->attacks[count].moveset.beams[i].texture.height};
                boss->attacks[count].moveset.beams[i].pos=(Vector2){boss->attacks[count].moveset.beams[i].hurtbox.x,boss->attacks[count].moveset.beams[i].hurtbox.y};
                boss->attacks[count].moveset.beams[i].delay=beamtimeJSON->valueint*z;
                boss->attacks[count].moveset.total++;
                break;
            }
        }
    }
}