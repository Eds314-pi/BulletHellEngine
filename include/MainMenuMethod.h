#include "../include/3rdPartyIncludes.h"
#include "Selector.h"
#include "SplashScreen.h"
#define GAME_WIDTH 800
#define GAME_HEIGHT 600

struct fileList readFightFiles();
void drawFileList(struct fileList*);
struct Selector InitalizeSelector(struct fileList*);
void updateSelector(struct Selector*);
void drawSelector(struct Selector*);