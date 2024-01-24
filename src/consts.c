#include "consts.h"

int winWidth = 1280;
int winHeight = 720;

int subWinOpen = 0;

int getWinWidth() {
    return winWidth;
}

int getWinHeight() {
    return winHeight;
}

int getSubWinOpen() {
    return subWinOpen;
}

void setSubWinOpen(int newOpen) {
    subWinOpen = newOpen;
}
