#include "../include/SplashScreen.h"
struct Splash setScreen()
{
    struct Splash crow={0};
    crow.text=LoadTexture("../images/Crow.png");
    crow.src=(Rectangle){0,0,crow.text.width,crow.text.height};
    crow.timer=0;
    bool done;
    return crow;
}
void drawScreen(struct Splash* background, int gameWidth, int gameHeight)
{
    DrawTexturePro(background->text,
        background->src,
        (Rectangle){100,100,gameWidth/3 ,gameHeight/3},
        (Vector2){0,0},
        0.0f,
        WHITE);

    background->timer++;
    if(background->timer==60)
    {
        background->done=true;
        background->timer=0;
    }
}