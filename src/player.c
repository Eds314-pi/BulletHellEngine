#include "../include/runMethods.h"
#include <cjson/cJSON.h>
#include <raylib.h>
void updatePlayer(struct player *player, struct area *area)
{
    if(player->freeMoveY)
    {
        
        if(IsKeyDown(KEY_UP) && (player->dest.y-player->accely)>area->playable.y) {player->dest.y-=player->accely;}
        if(IsKeyDown(KEY_DOWN) && (player->dest.y+player->accely+player->dest.height)<(area->playable.y+area->playable.height)) {player->dest.y+=player->accely;}
    }else{
        if(IsKeyPressed(KEY_UP) && player->liney>1) {player->liney--; player->dest.y=area->locky[player->liney]-player->dest.height/2;}
        if(IsKeyPressed(KEY_DOWN) && player->liney<area->liney-1) {player->liney++; player->dest.y=area->locky[player->liney]-player->dest.height/2;}
    }
    if(player->freeMoveX)
    {
        if(IsKeyDown(KEY_RIGHT) && (player->dest.x+player->accelx+player->dest.width)<(area->playable.x+area->playable.width)){player->dest.x+=player->accelx;}
        if(IsKeyDown(KEY_LEFT) && (player->dest.x-player->accelx)>area->playable.x) {player->dest.x-=player->accelx;}
    }else{
        if(IsKeyPressed(KEY_RIGHT) && player->linex<area->linex-1) {player->linex++; player->dest.x=area->lockx[player->linex]-player->dest.width/2;}
        if(IsKeyPressed(KEY_LEFT) && player->linex>1) {player->linex--; player->dest.x=area->lockx[player->linex]-player->dest.width/2;}
    }
    player->beamCollison[0] = (Vector2){player->dest.x, player->dest.y};
    player->beamCollison[1] = (Vector2){player->dest.x + player->dest.width, player->dest.y};
    player->beamCollison[2] = (Vector2){player->dest.x, player->dest.y + player->dest.height};
    player->beamCollison[3] = (Vector2){player->dest.x + player->dest.width, player->dest.y + player->dest.height};
    if(player->immunity)
    {
        player->currentHealth.width=player->maxHealth.width*((double)player->health/(double)player->startHealth);
        player->time--;
        if(player->time%30==0)
        {
            player->swap=!player->swap;
        }
        if(player->swap)
        {
            player->color=GRAY;
        }else{
            player->color=WHITE;
        }
        if(player->time==0)
        {
            player->swap=true;
            player->time=IMMUNITY_TIMER;
            player->immunity=false;
        }
    }else
        {
            player->color=WHITE;
        }
}
void Drawplayer(struct player *player)
{
    DrawRectangle(player->dest.x,player->dest.y,player->dest.width,player->dest.height,BLANK);
    DrawTexturePro(player->texture,player->scource,player->dest,player->origin,0.0f,player->color);
    DrawRectangle(player->maxHealth.x,player->maxHealth.y,player->maxHealth.width,player->maxHealth.height,RED);
    DrawRectangle(player->currentHealth.x,player->currentHealth.y,player->currentHealth.width,player->currentHealth.height,YELLOW);

}

void playerModifer(cJSON *move, struct fight *boss, int count)
{
    cJSON* textureJSON=cJSON_GetObjectItem(move, "texture");
    cJSON* player_x=cJSON_GetObjectItem(move, "player_x");
    cJSON* player_y=cJSON_GetObjectItem(move, "player_y");
    cJSON* player_width=cJSON_GetObjectItem(move, "player_width");
    cJSON* player_height=cJSON_GetObjectItem(move, "player_height");
    cJSON* player_speedX=cJSON_GetObjectItem(move, "player_speedX");
    cJSON* player_speedY=cJSON_GetObjectItem(move, "player_speedY");
    cJSON* freeMoveX=cJSON_GetObjectItem(move, "freeMoveX");
    cJSON* freeMoveY=cJSON_GetObjectItem(move, "freeMoveY");
    cJSON* delay=cJSON_GetObjectItem(move, "delay");
    if(player_x!=NULL)
    {
        boss->events[boss->currentEvent].orders.playa.dest.x=player_x->valueint;
    }else{
        boss->events[boss->currentEvent].orders.playa.dest.x=-1;
    }

    if(player_y!=NULL)
    {
        boss->events[boss->currentEvent].orders.playa.dest.y=player_y->valueint;
    }else{
        boss->events[boss->currentEvent].orders.playa.dest.y=-1;
    }

    if(player_width!=NULL)
    {
        boss->events[boss->currentEvent].orders.playa.dest.width=player_width->valuedouble*GetScreenWidth();
    }else {
        boss->events[boss->currentEvent].orders.playa.dest.width=-1;
    }

    if(player_height!=NULL)
    {
        boss->events[boss->currentEvent].orders.playa.dest.height=player_height->valuedouble*GetScreenWidth();
    }else{
        boss->events[boss->currentEvent].orders.playa.dest.height=-1;
    }

    if(player_speedX!=NULL)
    {
        boss->events[boss->currentEvent].orders.playa.accelx=player_speedX->valueint;
    }else{
        boss->events[boss->currentEvent].orders.playa.accelx=-1;
    }

    if(player_speedY!=NULL)
    {
        boss->events[boss->currentEvent].orders.playa.accely=player_speedY->valueint;
    }else{
        boss->events[boss->currentEvent].orders.playa.accely=-1;
    }
    boss->events[boss->currentEvent].orders.timer=delay->valueint;
    //ID for player modification
    boss->events[boss->currentEvent].orders.id=1;

    if(textureJSON!=NULL)
    {
        char texture[250];
        sprintf(texture,"../images/%s",textureJSON->valuestring);
        boss->events[boss->currentEvent].orders.playa.texture=LoadTexture(texture);
        boss->events[boss->currentEvent].orders.playa.scource=(Rectangle){0,0, boss->events[boss->currentEvent].orders.playa.texture.width, boss->events[boss->currentEvent].orders.playa.texture.height};
    }

    if(freeMoveX!=NULL)
    {
        char movement=freeMoveX->valuestring[0];
        switch(movement)
        {
            case 'Y':
                boss->events[boss->currentEvent].orders.playa.freeMoveX=true;
                break;
            case 'N':
                boss->events[boss->currentEvent].orders.playa.freeMoveX=false;
                break;
        }
    }

    if(freeMoveY!=NULL)
    {
        char movement=freeMoveY->valuestring[0];
        switch(movement)
        {
            case 'Y':
                boss->events[boss->currentEvent].orders.playa.freeMoveY=true;
                break;
            case 'N':
                boss->events[boss->currentEvent].orders.playa.freeMoveY=false;
                break;
        }
    }



}