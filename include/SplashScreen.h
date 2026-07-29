#include "3rdPartyIncludes.h"
struct Splash
{
    Texture2D text;
    Rectangle src;
    Sound audio;  
    bool done;
    int timer;
};
struct Splash setScreen();
void drawScreen(struct Splash* background, int gameWidth, int gameHeight);
