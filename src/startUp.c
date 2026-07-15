#include "../include/readFile.h"
#include "../include/runMethods.h"
char* readFile(char* name)
{\
    //ignores "\n"
    FILE* file=fopen(name,"rb");
    if(file==NULL)
    {
        puts("Failed to find file");
        return NULL;
    }

    fseek(file,0,SEEK_END);
    long size=ftell(file);
    rewind(file);
    char* buffer=malloc(size+1);

    fread(buffer,1,size,file);
    buffer[size]='\0';
    fclose(file);
    return buffer;
}
void openFile(char* fileName, struct fight *boss)
{
    char name[250];
    sprintf(name, "../fights/%s",fileName);
    char* json=readFile(name);
    cJSON* fight = cJSON_Parse(json);
    cJSON* attacks = cJSON_GetObjectItem(fight, "attacks");
    cJSON* attack = cJSON_GetArrayItem(attacks, 0);
    cJSON* attackCountJSON = cJSON_GetObjectItem(fight,"attackcount");
    int i=0;
    cJSON_ArrayForEach(attack, attacks)
    {
        cJSON *moveset=cJSON_GetObjectItem(attack,"moveset");
        typeHandler(moveset, boss,i);
        i++;
    }
    
    
    cJSON_Delete(fight);
    free(json);
}