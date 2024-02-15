#pragma once

#include <stdio.h>
#include <gtk/gtk.h>
#include "newUser.h"
#include "consts.h"

struct loginData {
    int index;
    GtkWidget *loginWin;
};

void login(GtkWidget *win, gpointer ptr);

void openLoginWin(GtkWidget *win, gpointer ptr);
