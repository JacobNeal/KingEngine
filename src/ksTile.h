/********************************************************
* Class:            ksTile
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksTile.h
*
*   Overview:
*       Class that contains the 4 points that make up
*       a tile:
*           TL  -   Top Left
*           TR  -   Top Right
*           BL  -   Bottom Left
*           BR  -   Bottom Right
*
********************************************************/

#ifndef KS_TILE_H
#define KS_TILE_H

#include "ksVector2D.h"

struct ksTile
{
    ksVector2D TL;
    ksVector2D TR;
    ksVector2D BL;
    ksVector2D BR;
};

#endif
