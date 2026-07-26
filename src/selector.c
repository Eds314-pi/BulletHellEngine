#include "../include/3rdPartyIncludes.h"
#include "../include/Selector.h"
struct Selector InitalizeSelector(struct fileList* list)
{
    struct Selector selector;
    selector.list=*list;
    selector.position=(Rectangle)
    {
        list->rowPos[1]-60,
        list->colPos[1],
        50,
        50
        
    };
    selector.text=LoadTexture("../images/Selector.png");
    selector.index=1;
    selector.gameStart=false;
    return selector;
}

void updateSelector(struct Selector* selector)
{
    if(IsKeyPressed(KEY_DOWN))
    {
        if(selector->index<=selector->list.count-1)
        {
            selector->index++;
        }
        if(selector->index==selector->list.count)
        {
            selector->index=1;
        }
        selector->position.x=selector->list.rowPos[selector->index]-60;
        selector->position.y=selector->list.colPos[selector->index];
    }
    if(IsKeyPressed(KEY_UP))
    {
        if(selector->index>=1)
        {
            selector->index--;
        }
        if(selector->index==0)
        {
            selector->index=selector->list.count-1;
        }
        selector->position.x=selector->list.rowPos[selector->index]-60;
        selector->position.y=selector->list.colPos[selector->index];
    }
    if(IsKeyPressed(KEY_RIGHT))
    {
        selector->gameStart=true;
    }
}

void drawSelector(struct Selector* selector)
{
    DrawTexturePro
    (
        selector->text,
        (Rectangle){0,0,selector->text.width,selector->text.height},
        selector->position,
        (Vector2){0,0},
        0.0f,
        WHITE
    );
}