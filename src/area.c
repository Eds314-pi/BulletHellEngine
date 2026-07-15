#include "../include/runMethods.h"
void updateArea(struct player *player, struct area *area)
{
    if(!player->freeMoveX)
    {
        for(int i=1;i<area->linex;i++)
        {
            area->lockx[i]=(int)(area->playable.width/area->linex)*i+area->playable.x;
        }
    }else{
        for(int i=0;i<area->linex;i++)
        {
            area->lockx[i]=0;
        }
    }

    if(!player->freeMoveY)
    {
        for(int i=1;i<area->liney;i++)
        {
            area->locky[i]=(int)(area->playable.height/area->liney)*i+area->playable.y;
        }
    }else{
        for(int i=0;i<area->liney;i++)
        {
            area->locky[i]=0;
        }
    }
}
void DrawArea(struct area *area)
{
    DrawRectangleLines(area->playable.x,area->playable.y,area->playable.width,area->playable.height,WHITE);
    for(int i=0;i<area->linex;i++)
    {
        DrawLine(area->lockx[i],area->playable.y,area->lockx[i],area->playable.height+area->playable.y,RED);
    }
    for(int i=0;i<area->liney;i++)
    {
        DrawLine(area->playable.x,area->locky[i],area->playable.x+area->playable.width,area->locky[i],RED);
    }
}

