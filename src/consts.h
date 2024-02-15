#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <sqlite3.h>
#include <gtk/gtk.h>

typedef enum {
    d_good,
    d_bad,
    d_none,
    d_strange 
} dreamType;

struct DATE{
    int d;
    int m;
    int y;
};

struct USERDATA {
    int date;
    dreamType type;
    bool drunk;
    bool insomnia;
    int melatonin;
    char content[1050];
};

extern int subWinOpen;
extern bool loggedIn;

extern int getWinWidth();
extern int getWinHeight();

extern int getSubWinOpen();
extern void setSubWinOpen(int newOpen);

extern bool checkDir(char* dirname);

extern void openFile(char* newFilename);
static int sqliteCallback(void *notUsed, int argc, char **argv, char **colName);
extern void initTable();
extern void writeFile(struct USERDATA userdata);
extern void readFile();
extern void closeFile();

// struct DATE getDate();
int getDate();

void closeSubWin(GtkWidget *widget, gpointer ptr);
