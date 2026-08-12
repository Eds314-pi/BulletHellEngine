#include "../include/readFile.h"
#include "../include/runMethods.h"
char* readFile(char* name)
{\
    //ignores "\n"
    FILE* file=fopen(name,"rb");
    if(file == NULL)
{
    printf("FAILED TO FIND FILE: %s\n", name);
    perror("fopen");
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
    sprintf(name, "%s/fights/%s",boss->path,fileName);
    char* json=readFile(name);
    cJSON* fight = cJSON_Parse(json);
    cJSON* attacks = cJSON_GetObjectItem(fight, "attacks");
    cJSON* attack = cJSON_GetArrayItem(attacks, 0);
    cJSON* attackCountJSON = cJSON_GetObjectItem(fight,"attackcount");
    cJSON* events = cJSON_GetObjectItem(fight, "event");
    cJSON* event = cJSON_GetArrayItem(events, 0);
  
    int i=0;
    cJSON_ArrayForEach(attack, attacks)
    {
        cJSON *moveset=cJSON_GetObjectItem(attack,"moveset");
        typeHandler(moveset, boss,i);
        i++;
    }
    i=0;
    cJSON_ArrayForEach(event, events)
    {
        cJSON *command=cJSON_GetObjectItem(event,"commands");
        printf("Commands: %d\n", cJSON_GetArraySize(command));
        commandHandler(command,boss,i);
        i++;
    }
    
    
    cJSON_Delete(fight);
    free(json);
}
