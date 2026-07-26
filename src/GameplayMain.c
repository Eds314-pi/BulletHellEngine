#include "../include/runMethods.h"
#include "../include/readFile.h"
int gameplay(char* argv, bool* playing)
{
    char* fileName=argv;
    //SetWindowSize(monitorw, monitorh);
    int ScreenWidth=GAME_WIDTH;
    int ScreenHeight=GAME_HEIGHT;
    //Sound hurty=LoadSound("../sounds/hurt.mp3");
    Sound beam=LoadSound("../sounds/blaster.mp3");
    RenderTexture2D target=LoadRenderTexture(GAME_WIDTH,GAME_HEIGHT);
    struct fight *boss = calloc(1, sizeof(struct fight));
    struct bullet bullets[MAX_BULLETS]={0};
    struct beam beams[MAX_BEAMS]={0};
    struct spawner spawners[MAX_SPAWNERS]={0};
    struct area playableArea= {0};
    struct background background= {0};
    
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
    player.health=1000;
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
    openFile(fileName,boss);
    
    while (!WindowShouldClose())    
    {
        if(IsKeyPressed(KEY_TAB))
        {
            *playing=false;
            break;
        }
        if(player.health>0)updateAttack(boss, bullets, beams, spawners);
        if(player.health>0)updateArea(&player,&playableArea);
        if(player.health>0)updatePlayer(&player, &playableArea);
        if(player.health>0)updateBullets(bullets,player.audio,player.dest, &player.immunity,&player.health);
        if(player.health>0)updateBeams(beams,player.audio,beam,player.beamCollison,&player.immunity,&player.health);
        if(player.health>0)updateSpawner(spawners,beams,bullets, player.dest, player.audio,&player.immunity, &player.health);
        if(player.health>0)updateEvent(boss, &player, &playableArea, &background);
        if(player.health<=0)
        {
            player.gameOver=true;
        }
        BeginTextureMode(target);
        if(!player.gameOver)
        {
            ClearBackground(BLACK);
            DrawArea(&playableArea);
            Drawplayer(&player);
            DrawBullets(bullets,player.audio,player.dest, &player.immunity,&player.health);
            DrawBeams(beams,player.audio,beam,player.beamCollison,&player.immunity,&player.health);
            DrawSpawner(spawners,beams,bullets, player.dest, &player.immunity, &player.health);
        }else{
            DrawBackground(&background);
        }
            EndTextureMode();
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(target.texture,(Rectangle){0, 0, GAME_WIDTH, -GAME_HEIGHT},(Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},(Vector2){0,0},0,WHITE);
            EndDrawing();
        
    }
    UnloadSound(player.audio);  
    *playing=false;
    return 0;
}
