#include "../include/readFile.h"
#include "../include/runMethods.h"
void typeHandler(cJSON* moveset, struct fight *boss, int count)
{
    cJSON* moves = cJSON_GetObjectItem(moveset, "moves");
    cJSON* move;
    int i=0;
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
                    printf("category: %c, type: %c\n", cat, type);
                        bulletSMaker(move, boss, count);
                        break;
                    case'R':
                    printf("category: %c, type: %c\n", cat, type);
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
        }
        i++;
    }

    
    

}