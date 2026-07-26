#pragma once
#include "3rdPartyIncludes.h"

#define MAX_LINEX 100
#define MAX_LINEY 100

struct area
    {
        Texture2D background;
        Rectangle playable;
        int lockx[MAX_LINEX];
        int locky[MAX_LINEY];
        int linex;
        int liney;

    };