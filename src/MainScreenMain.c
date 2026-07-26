#include "../include/runMethods.h"
#include "../include/MainMenuMethod.h"
int main(int argc, char* argv[])
{
    InitWindow(600,800,"Main Menu");
    RenderTexture2D target=LoadRenderTexture(GAME_WIDTH,GAME_HEIGHT);
    ToggleFullscreen();
    int ScreenWidth=GAME_WIDTH;
    int ScreenHeight=GAME_HEIGHT;
    InitAudioDevice();
    SetTargetFPS(60);               
    bool playing=false;
    
    struct fileList list=readFightFiles();
    struct Selector selector=InitalizeSelector(&list);


    for(int i = 1; i < list.count; i++)
    {
        printf("%s\n", list.fileName[i]);
    }


    int debugX=0;
    while(!WindowShouldClose())
    {
        BeginTextureMode(target);
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
            gameplay(list.fileName[selector.index],&playing);
        }   
        //debugX++;





        EndTextureMode();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(target.texture,(Rectangle){0, 0, GAME_WIDTH, -GAME_HEIGHT},(Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},(Vector2){0,0},0,WHITE);
        EndDrawing();
    }
    
   
    CloseAudioDevice();
    CloseWindow();        
}