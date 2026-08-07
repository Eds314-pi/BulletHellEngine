#include "../include/runMethods.h"
#include "../include/readFile.h"
#include <cjson/cJSON.h>


//struct bullet bullets[MAX_BULLETS]={0};
void updateBullets(struct bullet bullets[], Sound hurty, Rectangle dest, bool* immunity, int* health)
{
    
    for(int i=0;i<MAX_BULLETS;i++)
    {
        if(bullets[i].lifetime!=0)
        {
            bullets[i].lifetime--;
            if(bullets[i].follow)
            {
                bullets[i].velocx=bullets[i].maxVecx*cos(atan2(dest.y-bullets[i].hurtbox.y,dest.x-bullets[i].hurtbox.x));
                bullets[i].velocy=bullets[i].maxVecy*sin(atan2(dest.y-bullets[i].hurtbox.y,dest.x-bullets[i].hurtbox.x));
            }

            if(bullets[i].gravity)
            {
                switch(bullets[i].direction)
                {
                    case 'L':
                        bullets[i].velocx-=bullets[i].gravStrength;
                        break;
                    case'R':
                        bullets[i].velocx+=bullets[i].gravStrength;
                        break;
                    case'U':
                        bullets[i].velocy-=bullets[i].gravStrength;
                        break;
                    case'D':
                        bullets[i].velocy+=bullets[i].gravStrength;
                        break;
                }
            }
            bullets[i].hurtbox.x+=bullets[i].velocx;
            bullets[i].hurtbox.y+=bullets[i].velocy;
            if(CheckCollisionRecs(dest,bullets[i].hurtbox) && !(*immunity) && bullets[i].damage>0)
            {

                bullets[i].lifetime=0;
                *health-=bullets[i].damage;
                PlaySound(hurty);
                *immunity=true;
            }
            if(bullets[i].lifetime==0)
            {
                bullets[i]=(struct bullet){0};
            }
        }
    }

}
void DrawBullets(struct bullet bullets[], Sound hurty, Rectangle dest, bool* immunity, int* health)
{
    for(int i=0;i<MAX_BULLETS;i++)
    {
        if(bullets[i].lifetime!=0)
        {
            DrawRectangle(bullets[i].hurtbox.x,bullets[i].hurtbox.y,bullets[i].hurtbox.width,bullets[i].hurtbox.height,BLANK);
            DrawTexturePro(bullets[i].texture,bullets[i].scource,bullets[i].hurtbox,bullets[i].pos,0.0f,WHITE);   
        }
    }
}

void bulletSMaker(cJSON *attack, struct fight *boss, int count)
{
    cJSON* textureJSON = cJSON_GetObjectItem(attack,"texture");
    cJSON* posXJSON=cJSON_GetObjectItem(attack,"pos_x");
    cJSON* posYJSON=cJSON_GetObjectItem(attack,"pos_y");
    cJSON* velocXJSON=cJSON_GetObjectItem(attack,"veloc_x");
    cJSON* velocyJSON=cJSON_GetObjectItem(attack,"veloc_y");
    cJSON* widthJSON=cJSON_GetObjectItem(attack,"width");
    cJSON* heightJSON=cJSON_GetObjectItem(attack,"height");
    cJSON* damageJSON=cJSON_GetObjectItem(attack,"damage");
    cJSON* followJSON=cJSON_GetObjectItem(attack,"follow");
    cJSON* lifetimeJSON=cJSON_GetObjectItem(attack,"lifetime");
    cJSON* delayJSON=cJSON_GetObjectItem(attack,"delay");

    cJSON* gravityJSON=cJSON_GetObjectItem(attack, "gravity");
    cJSON* gravity_DirectionJSON=cJSON_GetObjectItem(attack, "gravity_direction");
    cJSON* gravity_strengthJSON=cJSON_GetObjectItem(attack, "gravity_stength");
    char texture[250];
    sprintf(texture,"%s/images/%s",boss->path,textureJSON->valuestring);
    printf("MAX_BULLETS: %d\n", MAX_BULLETS);
    for(int i=0;i<MAX_BULLETS;i++)
    {
        if(boss->attacks[count].moveset.bullets[i].lifetime==0)
        {
            boss->attacks[count].moveset.bulletTimer[i]=delayJSON->valueint;
            boss->attacks[count].moveset.bullets[i].texture=LoadTexture(texture);
            boss->attacks[count].moveset.bullets[i].hurtbox.x=posXJSON->valueint;
            boss->attacks[count].moveset.bullets[i].hurtbox.y=posYJSON->valueint;
            boss->attacks[count].moveset.bullets[i].hurtbox.width=GAME_WIDTH*widthJSON->valuedouble;
            boss->attacks[count].moveset.bullets[i].hurtbox.height=GAME_HEIGHT*heightJSON->valuedouble;
            boss->attacks[count].moveset.bullets[i].maxVecx=velocXJSON->valueint;
            boss->attacks[count].moveset.bullets[i].maxVecy=velocyJSON->valueint;
            boss->attacks[count].moveset.bullets[i].damage=damageJSON->valueint;
            boss->attacks[count].moveset.bullets[i].lifetime=lifetimeJSON->valueint;
            boss->attacks[count].moveset.bullets[i].scource=(Rectangle){0,0,boss->attacks[count].moveset.bullets[i].texture.width ,boss->attacks[count].moveset.bullets[i].texture.height};
            boss->attacks[count].moveset.total++;
            char fol=followJSON->valuestring[0];
            switch(fol)
            {
                case('N'):
                    boss->attacks[count].moveset.bullets[i].follow=false;
                    boss->attacks[count].moveset.bullets[i].velocx=boss->attacks[count].moveset.bullets[i].maxVecx;
                    boss->attacks[count].moveset.bullets[i].velocy=boss->attacks[count].moveset.bullets[i].maxVecy;
                    break;
                case('Y'):
                    boss->attacks[count].moveset.bullets[i].follow=true;
            }
            if(gravityJSON!=NULL)
            {
                char grav=gravityJSON->valuestring[0];
                switch(grav)
                {
                    case('Y'):
                        boss->attacks[count].moveset.bullets[i].gravity=true;
                        boss->attacks[count].moveset.bullets[i].gravStrength=gravity_strengthJSON->valueint;
                        char direc=gravity_DirectionJSON->valuestring[0];
                        switch(direc)
                        {
                            case 'L':
                                boss->attacks[count].moveset.bullets[i].direction='L';
                                break;
                            case'R':
                                boss->attacks[count].moveset.bullets[i].direction='R';
                                break;
                            case'U':
                                boss->attacks[count].moveset.bullets[i].direction='U';
                                break;
                            case'D':
                                boss->attacks[count].moveset.bullets[i].direction='D';
                                break;
                        }
                        break;
                    case('N'):
                        boss->attacks[count].moveset.bullets[i].gravity=false;

                }
            }else{
                boss->attacks[count].moveset.bullets[i].gravity=false;
            }
            break;
        }
    }
}

void bulletRMaker(cJSON *move, struct fight *boss, int count)
{
   
    char texture[250];
    cJSON* textureJSON=cJSON_GetObjectItem(move,"texture");
    cJSON* numberJSON=cJSON_GetObjectItem(move,"number");
    cJSON* pos_xJSON=cJSON_GetObjectItem(move,"pos_x");
    cJSON* seperation_xJSON=cJSON_GetObjectItem(move,"seperation_x");
    cJSON* pos_yJSON=cJSON_GetObjectItem(move,"pos_y");
    cJSON* seperation_yJSON=cJSON_GetObjectItem(move,"seperation_y");
    cJSON* veloc_xJSON=cJSON_GetObjectItem(move,"veloc_x");
    cJSON* varveloc_xJSON=cJSON_GetObjectItem(move,"+-veloc_x");
    cJSON* veloc_yJSON=cJSON_GetObjectItem(move,"veloc_y");
    cJSON* varveloc_yJSON=cJSON_GetObjectItem(move,"+-veloc_y");
    cJSON* widthJSON=cJSON_GetObjectItem(move,"width");
    cJSON* heightJSON=cJSON_GetObjectItem(move,"height");
    cJSON* damageJSON=cJSON_GetObjectItem(move,"damage");
    cJSON* followJSON=cJSON_GetObjectItem(move,"follow");
    cJSON* lifetimeJSON=cJSON_GetObjectItem(move,"lifetime");
    cJSON* delayJSON=cJSON_GetObjectItem(move,"delay");

    cJSON* gravityJSON=cJSON_GetObjectItem(move, "gravity");
    cJSON* gravity_DirectionJSON=cJSON_GetObjectItem(move, "gravity_direction");
    cJSON* gravity_strengthJSON=cJSON_GetObjectItem(move, "gravity_stength");
    sprintf(texture,"%s/images/%s",boss->path,textureJSON->valuestring);
    float random=((float)rand()/RAND_MAX)*2.0f-1.0f;
    for(int z=0;z<numberJSON->valueint;z++)
    {
        for(int i=0;i<MAX_BULLETS;i++)
        {
            if(boss->attacks[count].moveset.bullets[i].lifetime==0)
            {
                
                boss->attacks[count].moveset.bulletTimer[i]=delayJSON->valueint;
                boss->attacks[count].moveset.bullets[i].texture=LoadTexture(texture);
                boss->attacks[count].moveset.bullets[i].hurtbox.x=pos_xJSON->valueint+seperation_xJSON->valuedouble*random;
                random=((float)rand()/RAND_MAX)*2.0f-1.0f;
                
                boss->attacks[count].moveset.bullets[i].hurtbox.y=pos_yJSON->valueint+seperation_yJSON->valuedouble*random;
                random=((float)rand()/RAND_MAX)*2.0f-1.0f;

                boss->attacks[count].moveset.bullets[i].hurtbox.width=GAME_WIDTH*widthJSON->valuedouble;
                boss->attacks[count].moveset.bullets[i].hurtbox.height=GAME_HEIGHT*heightJSON->valuedouble;

                boss->attacks[count].moveset.bullets[i].maxVecx=veloc_xJSON->valueint+varveloc_xJSON->valuedouble*random;
                random=((float)rand()/RAND_MAX)*2.0f-1.0f;

                boss->attacks[count].moveset.bullets[i].maxVecy=veloc_yJSON->valueint+varveloc_yJSON->valuedouble*random;
                boss->attacks[count].moveset.bullets[i].damage=damageJSON->valueint;
                boss->attacks[count].moveset.bullets[i].lifetime=lifetimeJSON->valueint;
                boss->attacks[count].moveset.bullets[i].scource=(Rectangle){0,0,boss->attacks[count].moveset.bullets[i].texture.width ,boss->attacks[count].moveset.bullets[i].texture.height};
                boss->attacks[count].moveset.total++;
                char fol=followJSON->valuestring[0];
                switch(fol)
                {
                    case('N'):
                        boss->attacks[count].moveset.bullets[i].follow=false;
                        boss->attacks[count].moveset.bullets[i].velocx=boss->attacks[count].moveset.bullets[i].maxVecx;
                        boss->attacks[count].moveset.bullets[i].velocy=boss->attacks[count].moveset.bullets[i].maxVecy;
                        break;
                    case('Y'):
                        boss->attacks[count].moveset.bullets[i].follow=true;
                }
                if(gravityJSON!=NULL)
                {
                    char grav=gravityJSON->valuestring[0];
                    switch(grav)
                    {
                        case('Y'):
                            boss->attacks[count].moveset.bullets[i].gravity=true;
                            boss->attacks[count].moveset.bullets[i].gravStrength=gravity_strengthJSON->valuedouble;
                            char direc=gravity_DirectionJSON->valuestring[0];
                            switch(direc)
                            {
                                case 'L':
                                    boss->attacks[count].moveset.bullets[i].direction='L';
                                    break;
                                case'R':
                                    boss->attacks[count].moveset.bullets[i].direction='R';
                                    break;
                                case'U':
                                    boss->attacks[count].moveset.bullets[i].direction='U';
                                    break;
                                case'D':
                                    boss->attacks[count].moveset.bullets[i].direction='D';
                                    break;
                            }
                            break;
                        case('N'):
                            boss->attacks[count].moveset.bullets[i].gravity=false;

                    }
                }else{
                    boss->attacks[count].moveset.bullets[i].gravity=false;
                }
                break;
            }
        }
    }


    
}