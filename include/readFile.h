#pragma once
#include "runMethods.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void openFile(char*, struct fight*);
void typeHandler(cJSON *attack, struct fight *boss, int count);
void bulletSMaker(cJSON *move, struct fight *boss, int count);
void bulletRMaker(cJSON *move, struct fight *boss, int count);
void beamSMaker(cJSON *move, struct fight *boss, int count);
void beamLMaker(cJSON *move, struct fight *boss, int count);