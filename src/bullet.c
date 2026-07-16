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
    char texture[250];
    sprintf(texture,"../images/%s",textureJSON->valuestring);
    printf("MAX_BULLETS: %d\n", MAX_BULLETS);
    for(int i=0;i<MAX_BULLETS;i++)
    {
        if(boss->attacks[count].moveset.bullets[i].lifetime==0)
        {
            boss->attacks[count].moveset.bulletTimer[i]=delayJSON->valueint;
            boss->attacks[count].moveset.bullets[i].texture=LoadTexture(texture);
            boss->attacks[count].moveset.bullets[i].hurtbox.x=posXJSON->valueint;
            boss->attacks[count].moveset.bullets[i].hurtbox.y=posYJSON->valueint;
            boss->attacks[count].moveset.bullets[i].hurtbox.width=GetScreenWidth()*widthJSON->valuedouble;
            boss->attacks[count].moveset.bullets[i].hurtbox.height=GetScreenHeight()*heightJSON->valuedouble;
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
            break;
        }
    }
}

void bulletRMaker(cJSON *move, struct fight *boss, int count)
{
    puts("started random");
    char texture[250];
    cJSON* textureJSON=cJSON_GetObjectItem(move,"texture");
    puts("next random");
    cJSON* numberJSON=cJSON_GetObjectItem(move,"number");
     puts("next random");
    cJSON* pos_xJSON=cJSON_GetObjectItem(move,"pos_x");
     puts("next random");
    cJSON* seperation_xJSON=cJSON_GetObjectItem(move,"seperation_x");
     puts("next random");
    cJSON* pos_yJSON=cJSON_GetObjectItem(move,"pos_y");
     puts("next random");
    cJSON* seperation_yJSON=cJSON_GetObjectItem(move,"seperation_y");
     puts("next random");
    cJSON* veloc_xJSON=cJSON_GetObjectItem(move,"veloc_x");
     puts("next random");
    cJSON* varveloc_xJSON=cJSON_GetObjectItem(move,"+-veloc_x");
     puts("next random");
    cJSON* veloc_yJSON=cJSON_GetObjectItem(move,"veloc_y");
     puts("next random");
    cJSON* varveloc_yJSON=cJSON_GetObjectItem(move,"+-veloc_y");
     puts("next random");
    cJSON* widthJSON=cJSON_GetObjectItem(move,"width");
     puts("next random");
    cJSON* heightJSON=cJSON_GetObjectItem(move,"height");
     puts("next random");
    cJSON* damageJSON=cJSON_GetObjectItem(move,"damage");
     puts("next random");
    cJSON* followJSON=cJSON_GetObjectItem(move,"follow");
     puts("next random");
    cJSON* lifetimeJSON=cJSON_GetObjectItem(move,"lifetime");
     puts("next random");
    cJSON* delayJSON=cJSON_GetObjectItem(move,"delay");
    sprintf(texture,"../images/%s",textureJSON->valuestring);
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

                boss->attacks[count].moveset.bullets[i].hurtbox.width=GetScreenWidth()*widthJSON->valuedouble;
                boss->attacks[count].moveset.bullets[i].hurtbox.height=GetScreenHeight()*heightJSON->valuedouble;

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
                puts("random worked");
                break;
            }
        }
    }


    
}