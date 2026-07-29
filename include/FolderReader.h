#include "3rdPartyIncludes.h"
#define MAX_FILES 50
#define MAX_FILELENGTH 256

struct fileList
{
    char fileName[MAX_FILES][MAX_FILELENGTH];
    int count;
    int colPos[MAX_FILES];
    int rowPos[MAX_FILES];
};
void assignFile(struct fileList*);

