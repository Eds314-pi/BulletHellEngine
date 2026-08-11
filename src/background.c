#include "../include/runMethods.h"
#include "../include/readFile.h"
#include <cjson/cJSON.h>
void DrawBackground(struct background *background)
{
    Rectangle src=(Rectangle){0,0,background->texture.width,background->texture.height};
    Rectangle dest=(Rectangle){0,0,GAME_WIDTH,GAME_HEIGHT};
    DrawTexturePro(background->texture,src,dest,(Vector2){0,0},0.0f,WHITE);
    DrawText(background->text,background->pos_x,background->pos_y,background->size,background->color);
}
void backgroundModifier(cJSON* move, struct fight* boss, int count)
{
    boss->events[boss->currentEvent].orders.id=3;
    boss->events[boss->currentEvent].orders.timer=0;
    cJSON* textureJSON=cJSON_GetObjectItem(move, "texture");
    cJSON* colorJSON=cJSON_GetObjectItem(move, "shade");
    cJSON* textJSON=cJSON_GetObjectItem(move,"text");
    cJSON* text_xJSON=cJSON_GetObjectItem(move, "pos_x");
    cJSON* text_yJSON=cJSON_GetObjectItem(move, "pos_y");
    cJSON* sizeJSON=cJSON_GetObjectItem(move, "size");
    char text [250];
    sprintf(text,"../images/%s",textureJSON->valuestring);
    boss->events[boss->currentEvent].orders.background.texture=LoadTexture(text);
    strcpy(boss->events[boss->currentEvent].orders.background.text,textJSON->valuestring);
    boss->events[boss->currentEvent].orders.background.pos_x=text_xJSON->valueint;
    boss->events[boss->currentEvent].orders.background.pos_y=text_yJSON->valueint;
    boss->events[boss->currentEvent].orders.background.size=sizeJSON->valueint;
    const char *hex = colorJSON->valuestring;
    unsigned int colorValue = strtoul(hex + 1, NULL, 16); // skip '#'
    boss->events[boss->currentEvent].orders.background.color =(Color){(colorValue >> 16) & 0xFF, (colorValue >> 8) & 0xFF,colorValue & 0xFF,255};

}
