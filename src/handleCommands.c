#include "../include/readFile.h"
#include "../include/runMethods.h"
#include <cjson/cJSON.h>
void typeHandler(cJSON* moveset, struct fight *boss, int count)
{
    cJSON* moves = cJSON_GetObjectItem(moveset, "moves");
    cJSON* move;
    //int i=0;
    int j=0;
    cJSON_ArrayForEach(move,moves)
    {
        cJSON* catJSON= cJSON_GetObjectItem(move,"category");
        cJSON* typeJSON = cJSON_GetObjectItem(move,"type");
        char cat=catJSON->valuestring[0];
        char type=typeJSON->valuestring[0];
        switch(cat)
        {
            case'B':
                switch(type)
                {
                    case'S':
                        bulletSMaker(move, boss, count);
                        break;
                    case'R':
                        bulletRMaker(move,boss,count);
                        break;
                }
            break;
            case'-':
                switch(type)
                {
                    case'S':
                        beamSMaker(move,boss,count);
                        break;
                    case'L':
                        beamLMaker(move,boss,count);
                        break;

                }
            case'S':
                switch(type)
                {
                    case'S':
                        spawnerSMaker(move,boss,count);
                        break;
                    case'E':
                        spawnerSeqMaker(move,boss,count);
                        break;
                }
        }
        //i++;
    }
}
void commandHandler(cJSON* commands,struct fight *boss, int count)
{
    cJSON *command = NULL;
cJSON_ArrayForEach(command, commands)
{
    cJSON *catJSON = cJSON_GetObjectItem(command, "category");

    if (!cJSON_IsString(catJSON))
        continue;

    switch (catJSON->valuestring[0])
    {
        case 'P':
            playerModifer(command, boss, count);
            boss->currentEvent++;
            break;
        case 'A':
            areModifier(command,boss,count);
            boss->currentEvent++;
            break;
        case'D':
            backgroundModifier(command,boss, count);
            boss->currentEvent++;
            break;
            
    }
}
}