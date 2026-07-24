#include "../include/runMethods.h"
#include <cjson/cJSON.h>
#include <raylib.h>
#include "../include/readFile.h"
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
    if(area->background.id!=0)
    {
        DrawTexturePro(area->background,(Rectangle){0,0,area->background.width,area->background.height},(Rectangle){0,0,GAME_WIDTH,GAME_HEIGHT},(Vector2){0,0},0.0f,WHITE);
    }
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

void areModifier(cJSON *command,struct fight *boss ,int count)
{
    cJSON* pos_x=cJSON_GetObjectItem(command, "pos_x");
    cJSON* pos_y=cJSON_GetObjectItem(command, "pos_y");
    cJSON* width=cJSON_GetObjectItem(command, "width");
    cJSON* height=cJSON_GetObjectItem(command, "height");
    cJSON* line_x=cJSON_GetObjectItem(command, "line_x");
    cJSON* line_y=cJSON_GetObjectItem(command, "line_y");
    cJSON* delay=cJSON_GetObjectItem(command, "delay");
    cJSON* background=cJSON_GetObjectItem(command, "background");

    boss->events[boss->currentEvent].orders.plyablearea.linex=line_x->valueint;
    boss->events[boss->currentEvent].orders.plyablearea.liney=line_y->valueint;
    boss->events[boss->currentEvent].orders.plyablearea.playable.height=height->valuedouble*GAME_HEIGHT;
    boss->events[boss->currentEvent].orders.plyablearea.playable.width=width->valuedouble*GAME_WIDTH;
    boss->events[boss->currentEvent].orders.plyablearea.playable.y=pos_y->valueint;
    boss->events[boss->currentEvent].orders.plyablearea.playable.x=pos_x->valueint;
    boss->events[boss->currentEvent].orders.id=2;
    boss->events[boss->currentEvent].orders.timer=delay->valueint;
    if(background!=NULL)
    {
        char texture [250];
        sprintf(texture,"../images/%s",background->valuestring);
        boss->events[boss->currentEvent].orders.plyablearea.background=LoadTexture(texture);
    }

}

void setPlayerX(struct player *player, struct area *playablearea)
{
    int distance=0;
    int mimimumDistance=9999;
    for(int i=1;i<playablearea->linex;i++)
    {
        distance=abs(playablearea->lockx[i]-player->dest.x);
        if(distance<mimimumDistance)
        {
            mimimumDistance=distance;
            player->linex=i;
        }
        player->linex++;
        player->linex--;
    }
    bool inArea=false;
    while(!inArea)
    {
        if(player->dest.x>playablearea->playable.x+playablearea->playable.width || player->dest.x<playablearea->playable.x)
        {
            if(player->dest.x<playablearea->playable.x)
            {
                player->dest.x+=playablearea->playable.x+playablearea->playable.width-player->dest.x-player->dest.width;
            }else{
                player->dest.x-=player->dest.x-playablearea->playable.x+playablearea->playable.width-player->dest.width;
            }
            
        }else{
            inArea=true;
        }
    }
}

void setPlayerY(struct player *player, struct area *playablearea)
{
    int distance=0;
    int mimimumDistance=9999;
    for(int i=1;i<playablearea->liney;i++)
    {
        distance=abs(playablearea->locky[i]-player->dest.y);
        
        if(distance<mimimumDistance)
        {
            mimimumDistance=distance;
            player->liney=i;
        }
        player->liney--;
        player->liney++;
    }
    bool inArea=false;
    while(!inArea)
    {
        if(player->dest.y>playablearea->playable.y+playablearea->playable.height || player->dest.y<playablearea->playable.y)
        {
            if(player->dest.y<playablearea->playable.y)
            {
                player->dest.y+=playablearea->playable.y+playablearea->playable.height-player->dest.y-player->dest.height;
            }else{
                player->dest.y-=player->dest.y-playablearea->playable.y+playablearea->playable.height-player->dest.height;
            }
            
        }else{
            inArea=true;
        }
    }
}
