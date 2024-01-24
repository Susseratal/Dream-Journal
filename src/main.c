#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gtk/gtk.h>

#include "consts.h"
#include "newDreamWin.h"
#include "newUser.h"
#include "login.h"

void endProgram(GtkWidget *win, gpointer ptr) {
    if(getSubWinOpen() == 0) {
        gtk_main_quit();
    }
}

/*
void saveText(GtkWidget *widget, gpointer ptr) {
    USERDATA *data = ptr;

    const char* input = gtk_entry_get_text(&ptr->txt);
    &ptr->username = input;
    // memcpy(ptr.username, input, sizeof(input));
}
*/

/*
void newAccountWin(USERDATA *u) {
    GtkWidget *subWin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(subWin), winWidth, winHeight); // set width and height
    gtk_window_set_resizable(GTK_WINDOW(subWin), FALSE); // set non-resizable
    gtk_window_set_title(GTK_WINDOW(subWin), "New User Account");

    GtkWidget *userName = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(userName), "Username");

    GtkWidget *closeBtn = gtk_button_new_with_label("Ok"); // Create a button with a label

    // &u->txt = userName;
    g_signal_connect(closeBtn, "clicked", G_CALLBACK(saveText), subWin); 
    g_signal_connect(subWin, "delete_event", G_CALLBACK(closeSubwin), subWin);

    GtkWidget *grd = gtk_grid_new();

    gtk_grid_attach(GTK_GRID(grd), userName, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), closeBtn, 0, 1, 1, 1);

    subWinOpen = 1;
    gtk_container_add(GTK_CONTAINER(subWin), grd); // add the grid to the window
    gtk_widget_show_all(subWin);
}
*/

/*
GtkWidget newBox(){
    GtkWidget *grd = gtk_grid_new();
    // add the values passed in as arguments to the box as a tile

}
*/

int main(int argc, char *argv[]) {
    openLoginWin();
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
    gtk_calendar_set_detail_height_rows(GTK_CALENDAR(cal), 2);

    GtkWidget *newBtn = gtk_button_new_with_label("New");
    g_signal_connect(newBtn, "clicked", G_CALLBACK(newDreamWin), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_box_pack_start(GTK_BOX(box), cal, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), newBtn, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(win), box);

    gtk_widget_show_all(win); // show everything in the window

    // FILE *fp;
    // fp = fopen("./users/", "rb");

    DIR* d;
    int n = 0;
    struct dirent *dir;

    d = opendir("users");
    if(!d) {
        mkdir("users", 0700);
        USERDATA newUserData;
        // newAccountWin(&newUserData);
        // TODO -- create struct definition for user data 
        // create struct object in main function which gets passed into newAccountWin 
        // newAccountWin writes into each of the value buffers for userData
        // userData is then used to create an actual new user file 
        // saving and loading arrays and 'objects' is a problem i'm somewhat kicking down the road
        // plus serialisation at some point ideally
    }
    else {
        while((dir = readdir(d)) != NULL) {
            if(n > 1) {
                printf("%s\n", dir->d_name);
            }
            n++;
        }
    }
    closedir(d);

    gtk_main(); // run it 
    return 0;
}
