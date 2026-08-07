#include "../include/FolderReader.h"
#define GAME_WIDTH 800
#define GAME_HEIGHT 600
struct fileList readFightFiles(char *path)
{
    DIR *folder;
    struct dirent *entry;
    struct fileList list={0};
    list.count=1;
    //printf("Before listing media\n");
    //findUSB();
    //printf("After listing media\n");

    findUSB(path);
    char fight[PATH_MAX];
    snprintf(fight,PATH_MAX,"%s/fights",path);
    folder=opendir(fight);
    
    if(folder==NULL)
    {
        puts("Folder not found\n");
        return list;
    }
    while((entry=readdir(folder))!=NULL)
    {
        if(entry->d_name[0]!='.')
        {
            strcpy(list.fileName[list.count], entry->d_name);
            list.count++;
            if(list.count==MAX_FILES)
            {
                break;
            }
        }
        
    }
    closedir(folder);

    for(int i=1;i<list.count;i++)
    {
        int column= GAME_HEIGHT*i/25;
        int row;
        if(i>25)
        {
            row= 320*(i/25);
            column= GAME_HEIGHT*(i%25)/25;
            list.colPos[i]=column;
            list.rowPos[i]=row;
        }else{
            row=50;
            list.colPos[i]=column;
            list.rowPos[i]=row;
        }
            
    }
    return list;
}

void drawFileList(struct fileList* list)
{
    for(int i=1;i<list->count;i++)
    {
        DrawText(list->fileName[i],list->rowPos[i],list->colPos[i],25,WHITE);
    }
}


char * findUSB(char* path)
{
    DIR *dir = opendir("/run/media");

    if (!dir)
    {
        perror("/run/media");
        return NULL;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue;

        snprintf(path,PATH_MAX,"/run/media/%s",entry->d_name);
        list_directory(path);
    }
    closedir(dir);
    return path;
}
char * list_directory(char *path) {
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0) {
            printf("%s/%s\n", path, entry->d_name);
            
            
            strncat(path, "/", PATH_MAX - strlen(path) - 1);
            strncat(path, entry->d_name, PATH_MAX - strlen(path) - 1);
        }
    }

    closedir(dir);
    return path;
}

