#pragma once

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "consts.h"

struct newUserData {
    int existingUsers;
    GtkWidget *loginWin;
};

void saveData(GtkWidget *widget, gpointer ptr);

void newUserWin(GtkWidget *win, gpointer ptr);
