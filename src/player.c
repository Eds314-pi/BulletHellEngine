#include "../include/runMethods.h"
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
