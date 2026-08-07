#include "../include/runMethods.h"
#include "../include/MainMenuMethod.h"
#include "rlgl.h"
int main(int argc, char* argv[])
{
    system("/usr/bin/python3 button2.py & echo $! > /tmp/button.pid");

    InitWindow(800,600,"Main Menu");
    RenderTexture2D target=LoadRenderTexture(GAME_WIDTH,GAME_HEIGHT);
    ToggleFullscreen();
    int ScreenWidth=GAME_WIDTH;
    int ScreenHeight=GAME_HEIGHT;
    InitAudioDevice();
    SetTargetFPS(60);               
    bool playing=false;
    char path [PATH_MAX];
    struct fileList list=readFightFiles(path);
    struct Selector selector=InitalizeSelector(&list);
    struct Splash background=setScreen();
    while(!WindowShouldClose())
    {
        BeginTextureMode(target);
        if(!playing)
        {
            if(background.done)
            {
                ClearBackground(BLACK);
                if(!playing)
                {
                    updateSelector(&selector);
                    drawSelector(&selector);
                    drawFileList(&list);
                }
                if(selector.gameStart)
                {
                    selector.gameStart=false;
                    playing=true;
                    gameplay(list.fileName[selector.index],&playing, path);
                    background.done=false;
                }   
            }else{
                ClearBackground(BLACK);
                drawScreen(&background,GAME_WIDTH,GAME_HEIGHT);
            
            }
        }
        



        EndTextureMode();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(target.texture,(Rectangle){0, 0, GAME_WIDTH, -GAME_HEIGHT},(Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},(Vector2){0,0},0,WHITE);
        EndDrawing();
    }
    
    system("kill $(cat /tmp/button.pid)");
    system("rm /tmp/button.pid");
    CloseAudioDevice();
    CloseWindow();        
}
