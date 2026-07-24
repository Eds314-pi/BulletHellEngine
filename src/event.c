#include "../include/runMethods.h"
#include "../include/readFile.h"
void updateEvent(struct fight* boss, struct player *player, struct area *playableArea, struct background *background)
{
    for(int i=0;i<MAX_EVENTS;i++)
    {
        if(boss->events[i].orders.timer>=0)
        {
            if(boss->events[i].orders.timer==0)
            {
                boss->events[i].orders.timer--;
                if(boss->events[i].orders.id==1)
                {
                    if(boss->events[i].orders.playa.dest.x!=-1)player->dest.x=boss->events[i].orders.playa.dest.x;
                    if(boss->events[i].orders.playa.dest.y!=-1) player->dest.y=boss->events[i].orders.playa.dest.y;
                    if(boss->events[i].orders.playa.dest.width!=-1) player->dest.width=boss->events[i].orders.playa.dest.width;
                    if(boss->events[i].orders.playa.dest.height!=-1) player->dest.height=boss->events[i].orders.playa.dest.height;
                    if(boss->events[i].orders.playa.accelx!=-1) player->accelx=boss->events[i].orders.playa.accelx;
                    if(boss->events[i].orders.playa.accely!=-1) player->accely=boss->events[i].orders.playa.accely;
                    if(boss->events[i].orders.playa.health!=-1) player->health=boss->events[i].orders.playa.health;
                    player->freeMoveX=boss->events[i].orders.playa.freeMoveX;
                    player->freeMoveY=boss->events[i].orders.playa.freeMoveY;
                    player->audio=boss->events[i].orders.playa.audio;
                    updateArea(player,playableArea);
                    setPlayerX(player,playableArea);
                    setPlayerY(player,playableArea);
                    if(boss->events[i].orders.playa.texture.id!=0) {player->texture=boss->events[i].orders.playa.texture;player->scource=boss->events[i].orders.playa.scource;}
                    }else if(boss->events[i].orders.id==2)
                    {
                        playableArea->playable=boss->events[i].orders.plyablearea.playable;
                        playableArea->linex=boss->events[i].orders.plyablearea.linex;
                        playableArea->liney=boss->events[i].orders.plyablearea.liney;
                        if(boss->events[i].orders.plyablearea.background.id!=0)
                        {
                            playableArea->background=boss->events[i].orders.plyablearea.background;
                        }
                    
                        updateArea(player,playableArea);
                        setPlayerX(player,playableArea);
                        setPlayerY(player,playableArea);
                    }else if(boss->events[i].orders.id==3)
                    {
                        background->texture=boss->events[i].orders.background.texture;
                        strcpy(background->text,boss->events[i].orders.background.text);
                        background->color=boss->events[i].orders.background.color;
                        background->pos_x=boss->events[i].orders.background.pos_x;
                        background->pos_y=boss->events[i].orders.background.pos_y;
                        background->size=boss->events[i].orders.background.size;
                        printf("Texture ID is :%d",background->texture.id);
                        puts("background copied");
                    }

            }else{
                boss->events[i].orders.timer--;
            }
        }
    }
}