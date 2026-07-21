#include "../include/runMethods.h"
#include "../include/readFile.h"
void updateEvent(struct fight* boss, struct player *player, struct area *playableArea)
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
                    player->freeMoveX=boss->events[i].orders.playa.freeMoveX;
                    player->freeMoveY=boss->events[i].orders.playa.freeMoveY;
                    updateArea(player,playableArea);
                    setPlayerX(player,playableArea);
                    setPlayerY(player,playableArea);
                    if(boss->events[i].orders.playa.texture.id!=0) {player->texture=boss->events[i].orders.playa.texture;player->scource=boss->events[i].orders.playa.scource;}
                }else if(boss->events[i].orders.id==2){
                    playableArea->playable=boss->events[i].orders.plyablearea.playable;
                    playableArea->linex=boss->events[i].orders.plyablearea.linex;
                   
                    playableArea->liney=boss->events[i].orders.plyablearea.liney;
                    
                    updateArea(player,playableArea);
                    setPlayerX(player,playableArea);
                    setPlayerY(player,playableArea);
                }

            }else{
                boss->events[i].orders.timer--;
            }
        }
    }
}