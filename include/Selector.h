#include "3rdPartyIncludes.h"
#include "FolderReader.h"
struct Selector
{
    Texture2D text;
    Rectangle position;
    struct fileList list;
    int index;
    bool gameStart;
};
struct Selector InitalizeSelector(struct fileList*);
void updateSelector(struct Selector*);
void drawSelector(struct Selector*);