#pragma once

#include <stdio.h>
#include <gtk/gtk.h>
#include "consts.h"

void closeDreamWin(GtkWidget *widget, gpointer ptr);
void dreamTypeChanged(GtkWidget *wid, gpointer ptr);
void newDreamWin(GtkWidget* win, gpointer ptr);
