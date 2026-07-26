#include "../include/3rdPartyIncludes.h"
#include "Selector.h"

#define GAME_WIDTH 3072
#define GAME_HEIGHT 1920

struct fileList readFightFiles();
void drawFileList(struct fileList*);
struct Selector InitalizeSelector(struct fileList*);
void updateSelector(struct Selector*);
void drawSelector(struct Selector*);