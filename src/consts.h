#pragma once

#include <stdio.h>

typedef struct {
    char* username;
} USERDATA;

extern int winWidth;
extern int winHeight;

extern int subWinOpen;

extern int getWinWidth();
extern int getWinHeight();

extern int getSubWinOpen();
extern void setSubWinOpen(int newOpen);
