#include "../include/runMethods.h"
#include "../include/readFile.h"
int main(int argc, char* argv[])
{
    char* fileName=argv[1];
    InitWindow(800, 600, "");
    ToggleFullscreen();
    //SetWindowSize(monitorw, monitorh);
    int ScreenWidth=GetScreenWidth();
    int ScreenHeight=GetScreenHeight();
    InitAudioDevice();
    SetTargetFPS(60);               
    Sound hurty=LoadSound("../sounds/hurt.mp3");
    Sound beam=LoadSound("../sounds/blaster.mp3");

    struct fight boss={0};
    openFile(fileName,&boss);
    struct bullet bullets[MAX_BULLETS]={0};
    struct beam beams[MAX_BEAMS]={0};
    struct spawner spawners[MAX_SPAWNERS]={0};
    struct area playableArea;
    
    playableArea.playable=(Rectangle){ScreenWidth/4,(int)(ScreenHeight/1.5),ScreenWidth/2,ScreenHeight/4};
    playableArea.linex=4;
    playableArea.liney=4;

    struct player player;
    //Evereything stays a constant regardless of screen size
    int playerx=ScreenWidth/3;
    int playery=(int)ScreenHeight/1.3;
    int playerw=ScreenWidth*.03;
    int playerh=ScreenWidth*.025;
    int accelx=ScreenWidth*.0035;
    int accely=ScreenHeight*.0035;
    
    //All player data
    player.immunity=false;
    player.swap=true;
    player.texture= LoadTexture("../images/Heart2.png");
    player.scource=(Rectangle){0,0,player.texture.width,player.texture.height};
    player.dest=(Rectangle){playerx,playery,playerw,playerh};
    player.origin=(Vector2){0,0};
    player.health=10;
    player.startHealth=10;
    player.gameOver=false;
    player.time=IMMUNITY_TIMER;
    player.currentHealth=(Rectangle){playableArea.playable.x,playableArea.playable.y+120+playableArea.playable.height,playableArea.playable.width,60};
    player.maxHealth=(Rectangle){playableArea.playable.x,playableArea.playable.y+120+playableArea.playable.height,playableArea.playable.width,60};
    player.accelx=accelx;
    player.accely=accely;
    player.freeMoveX=true;
    player.freeMoveY=true;
    player.linex=1;
    player.liney=1;

    
    while (!WindowShouldClose())    
    {
        if(player.health>0)updateAttack(&boss, bullets);
        if(player.health>0)updateArea(&player,&playableArea);
        if(player.health>0)updatePlayer(&player, &playableArea);
        if(player.health>0)updateBullets(bullets,hurty,player.dest, &player.immunity,&player.health);
        if(player.health>0)updateBeams(beams,hurty,beam,player.beamCollison,&player.immunity,&player.health);
        if(player.health>0)updateSpawner(spawners,beams,bullets, player.dest, hurty,&player.immunity, &player.health);
        if(player.health<=0)
        {
            player.gameOver=true;
        }
        BeginDrawing();
        if(!player.gameOver)
            {
                ClearBackground(BLACK);
                Drawplayer(&player);
                DrawArea(&playableArea);
                DrawBullets(bullets,hurty,player.dest, &player.immunity,&player.health);
                DrawBeams(beams,hurty,beam,player.beamCollison,&player.immunity,&player.health);
                DrawSpawner(spawners,beams,bullets, player.dest, &player.immunity, &player.health);
            }else{
                ClearBackground(BLACK);
            }
            


        EndDrawing();
        
    }
    UnloadSound(spawners[0].pop);
    UnloadSound(spawners[1].pop);
    UnloadSound(hurty);
    UnloadSound(beam);
    CloseAudioDevice();
    CloseWindow();        
    return 0;
}
