#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#include "consts.h"
#include "newDreamWin.h"
#include "newUser.h"
#include "login.h"

void endProgram(GtkWidget *win, gpointer ptr) {
    if(getSubWinOpen() == 0) {
        closeFile();
        gtk_main_quit();
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // Initialise GTK

    /* This all creates and formats the text entry window */
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Create a window 
    gtk_window_set_default_size(GTK_WINDOW(win), getWinWidth(), getWinHeight()); // set width and height
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE); // set non-resizable
    gtk_window_set_title(GTK_WINDOW(win), "Dream Journal");
    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);

    g_signal_connect(win, "delete_event", G_CALLBACK(endProgram), NULL); // connect the `x` in the toolbar to the endProgram function as well
    // inside this window i need to create a calendar-esque grid

    // for loop to create a grid of grid items - 1 for every day of the month
    // maintain an array of these

    GtkWidget *cal = gtk_calendar_new();
    // gtk_calendar_set_detail_height_rows(GTK_CALENDAR(cal), 2);
    gtk_widget_set_hexpand(GTK_WIDGET(cal), true); // set the blanking box to use as much width of the screen as possible
    gtk_widget_set_vexpand(GTK_WIDGET(cal), true); // set the blanking box to use as much width of the screen as possible

    GtkWidget *blank = gtk_label_new(""); // blanking block
    gtk_widget_set_hexpand(GTK_WIDGET(blank), true); // set the blanking box to use as much width of the screen as possible

    GtkWidget *grd = gtk_grid_new(); // create a new grid

    // attach everything to the grid
    gtk_grid_attach(GTK_GRID(grd), cal, 0, 0, 2, 2);
    gtk_grid_attach(GTK_GRID(grd), blank, 0, 1, 3, 1);

    gtk_container_add(GTK_CONTAINER(win), grd); // add the grid to the window

    // struct DATE d = getDate();
    // printf("%d-%d-%d\n", d.d, d.m, d.y);
    printf("%d\n", getDate());
    gtk_widget_show_all(win); // show everything in the window

    struct newUserData newData = {0, NULL};
    // newData.existingUsers = 0;
    // newData.loginWin = NULL;

    if(checkDir("users")) { // if this returns true, users dir has been created so we want to trigger the new users method
        newUserWin(NULL, &newData);
    }
    else {
        openLoginWin(NULL, NULL);
        // login
    }

    gtk_main(); // run it 
    return 0;
}
