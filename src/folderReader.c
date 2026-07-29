#include "../include/FolderReader.h"
#define GAME_WIDTH 800
#define GAME_HEIGHT 600
struct fileList readFightFiles()
{
    DIR *folder;
    struct dirent *entry;
    struct fileList list={0};
    list.count=1;
    folder=opendir("../fights");
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